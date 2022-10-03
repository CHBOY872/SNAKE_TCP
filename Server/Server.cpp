#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/select.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>

#include "Server.hpp"

FdHandler::~FdHandler() { close(fd); }

///////////////////////////////////////

EventSelector::~EventSelector()
{
    if (fd_array)
        delete[] fd_array;
}

void EventSelector::Add(FdHandler *h)
{
    int fd = h->GetFd();
    int i;
    if (!fd_array)
    {
        fd_array_len = fd >= fd_array_len_start ? fd + 1 : fd_array_len_start;
        fd_array = new FdHandler *[fd_array_len];
        for (i = 0; i < fd_array_len; i++)
            fd_array[i] = 0;
    }
    if (fd_array_len <= fd)
    {
        int new_fd_array_len = fd_array_len;
        while (fd_array_len <= fd)
            new_fd_array_len *= 2;
        FdHandler **tmp = new FdHandler *[new_fd_array_len];
        for (i = 0; i < new_fd_array_len; i++)
            tmp[i] = i < fd_array_len ? fd_array[i] : 0;
        delete[] fd_array;
        fd_array = tmp;
        fd_array_len = new_fd_array_len;
    }
    fd_array[fd] = h;
    if (fd > max_fd)
        max_fd = fd;
}

void EventSelector::Remove(FdHandler *h)
{
    int fd = h->GetFd();
    if (fd > fd_array_len || h != fd_array[fd])
        return;
    fd_array[fd] = 0;
    if (fd == max_fd)
    {
        while (fd_array[max_fd] && max_fd >= 0)
            max_fd--;
    }
}

void EventSelector::Run()
{
    struct timeval max_time;
    fd_set rds;
    fd_set wrs;
    int i, res;
    for (;;)
    {
        FD_ZERO(&rds);
        FD_ZERO(&wrs);
        for (i = 0; i <= max_fd; i++)
        {
            if (fd_array[i])
            {
                if (fd_array[i]->WantRead())
                    FD_SET(i, &rds);
                if (fd_array[i]->WantWrite())
                    FD_SET(i, &wrs);
            }
        }
        max_time.tv_usec = 500000;
        max_time.tv_sec = 0;
        struct timeval *t = server_fd->WantWrite() ? 0 : &max_time;
        res = select(max_fd + 1, &rds, &wrs, 0, t);
        if (res < 0)
        {
            perror("select");
            return;
        }
        if (res == 0)
        {
            server_fd->SetWrite(true);
            server_fd->Handle(false, true);
            continue;
        }
        for (i = 0; i <= max_fd; i++)
        {
            if (fd_array[i])
            {
                bool r = FD_ISSET(i, &rds);
                bool w = FD_ISSET(i, &wrs);
                if (r || w)
                    fd_array[i]->Handle(r, w);
            }
        }
    }
}

void EventSelector::SetServerFd(FdHandler *h)
{
    server_fd = h;
}

////////////////////////////////////

Server::Server(int _fd, EventSelector *_the_selector,
               Field *_field,
               GameHandlerGemstone *_handler, int _food_count)
    : FdHandler(_fd), first(0), the_selector(_the_selector), field(_field),
      handler(_handler), snakes_count(0), st(not_started),
      food_count(_food_count)
{
    the_selector->Add(this);
    the_selector->SetServerFd(this);
}

Server::~Server()
{
    while (first)
    {
        item *tmp = first->next;
        the_selector->Remove(tmp->cl);
        delete tmp->cl;
        delete first;
        first = tmp;
    }
}

Server *Server::Start(int port, EventSelector *_the_selector,
                      Field *_field,
                      GameHandlerGemstone *_handler, int _food_count)
{
    sockaddr_in addr;
    int opt = 1;
    int _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == _fd)
        return 0;
    setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_addr.s_addr = htons(INADDR_ANY);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    if (-1 == bind(_fd, (sockaddr *)&addr, sizeof(addr)))
        return 0;

    if (-1 == listen(_fd, fd_array_len_start))
        return 0;

    return new Server(_fd, _the_selector, _field, _handler, _food_count);
}

void Server::RemoveClient(Client *cl)
{
    item **p;
    ((SnakeHandler)*handler).RemoveSnake(cl->GetSnake());
    the_selector->Remove(cl);
    for (p = &first; *p; p = &((*p)->next))
    {
        if ((*p)->cl == cl)
        {
            item *tmp = *p;
            *p = tmp->next;
            delete tmp->cl;
            delete tmp;
            return;
        }
    }
}

void Server::Handle(bool r, bool w)
{
    if (r)
    {
        sockaddr_in addr;
        socklen_t len = 1;
        int _fd = accept(GetFd(), (struct sockaddr *)&addr, &len);
        if (-1 == _fd)
            return;
        item *tmp = new item;
        Snake *sn = new Snake(Position(rand() % field->GetSizeX(),
                                       rand() % field->GetSizeY()),
                              snakes_count, handler);
        snakes_count++;
        tmp->cl = new Client(_fd, this, sn);
        tmp->next = first;
        first = tmp;
        ((SnakeHandler)*handler).AddSnake(sn);
        the_selector->Add(tmp->cl);
    }
    if (w)
    {
        item *p = first;
        Snake *tmp_snake = 0;
        switch (st)
        {
        case started:
            while (p)
            {
                if (((SnakeHandler)*handler).IsSnake(p->cl->GetSnake()))
                {
                    item *tmp = p->next;
                    RemoveClient(p->cl);
                    p = tmp;
                    continue;
                }
                if (((SnakeHandler)*handler)
                        .IsOtherSnake(p->cl->GetSnake(), &tmp_snake))
                {
                    item *tmp = p->next;
                    RemoveClient(p->cl);
                    if (tmp_snake)
                    {
                        Client *cl = FindClientBySnake(tmp_snake);
                        RemoveClient(cl);
                        tmp_snake = 0;
                    }
                    p = tmp;
                    continue;
                }
                ((SnakeHandler)*handler).IsFood(p->cl->GetSnake());
                p = p->next;
            }
            p = first;
            while (p)
            {
                p->cl->GetSnake()->Move();
                p = p->next;
            }
            DrawAll();
            break;

        default:
            break;
        }

        SetWrite(false);
    }
}

void Server::DrawAll()
{
    item *p = first;
    ((DrawHandler)*handler).DrawField();
    while (p)
    {
        ((DrawHandler)*handler)
            .DrawFieldFor(p->cl->GetSnake());
        SendTo(p->cl->GetFd(), field->GetField(), field->GetFullLen());
        p = p->next;
    }
}

void Server::SendTo(int fd, const char *msg, int len)
{
    write(fd, msg, len);
}

void Server::StartGame()
{
    if (st != not_started)
        return;
    int i;
    for (i = 0; i < food_count; i++)
        ((FoodHandler)*handler).AddFood();
    st = started;
}

Client *Server::FindClientBySnake(Snake *s)
{
    item *p = first;
    while (p)
    {
        if (p->cl->GetSnake() == s)
            return p->cl;
        p = first->next;
    }
    return 0;
}

////////////////////////////////////

Client::Client(int _fd, Server *_the_master, Snake *_sn)
    : FdHandler(_fd), buf_used(0), sn(_sn), the_master(_the_master)
{
    memset(buf, 0, buffersize);
}

Client::~Client()
{
    delete sn;
}

void Client::Handle(bool r, bool w)
{
    if (!r)
        return;
    int i, pos = -1;
    int rc = read(GetFd(), buf + buf_used, buffersize - buf_used);
    if (0 >= rc)
    {
        the_master->RemoveClient(this);
        return;
    }
    for (i = 0; i < rc + buf_used; i++)
    {
        if (buf[i] == '\n')
        {
            pos = i;
            break;
        }
    }
    buf_used += rc;
    if (pos == -1)
        return;

    char *msg = new char[pos + 1];
    memcpy(msg, buf, pos);
    msg[pos] = 0;
    if (msg[pos - 1] == '\r')
        msg[pos - 1] = 0;

    StringHandle(msg);

    delete[] msg;
    memset(buf, 0, pos);
    buf_used = 0;
}

void Client::StringHandle(const char *msg)
{
    MoveVector s(0, 0);
    if (!strcmp(msg, ""))
    {
        the_master->StartGame();
    }
    else if (!strcmp(msg, "w"))
    {
        s = MoveVector(0, -1);
    }
    else if (!strcmp(msg, "s"))
    {
        s = MoveVector(0, 1);
    }
    else if (!strcmp(msg, "a"))
    {
        s = MoveVector(-1, 0);
    }
    else if (!strcmp(msg, "d"))
    {
        s = MoveVector(1, 0);
    }
    sn->ChangeDirection(&s);
}
