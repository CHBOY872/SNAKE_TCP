#ifndef SERVER_HPP_SENTRY
#define SERVER_HPP_SENTRY

#include "../Snake/Snake.hpp"
#include "../List/List.hpp"
#include "../Field/Field.hpp"
#include "../Food/Food.hpp"
#include "../GameHandler/GameHandler.hpp"

enum
{
    fd_array_len_start = 16,
    buffersize = 64
};

class FdHandler
{
    int fd;
    bool want_read, want_write;

public:
    FdHandler(int _fd, bool _want_read = true, bool _want_write = false)
        : fd(_fd), want_read(_want_read), want_write(_want_write) {}
    virtual ~FdHandler() {}

    int GetFd() { return fd; }
    bool WantRead() { return want_read; }
    bool WantWrite() { return want_write; }

    void SetRead(bool _want_read) { want_read = _want_read; }
    void SetWrite(bool _want_write) { want_write = _want_write; }

    virtual void Handle(bool r, bool w) = 0;
};

class EventSelector
{
    FdHandler **fd_array;
    int fd_array_len;
    int max_fd;
    FdHandler *server_fd;

public:
    EventSelector()
        : fd_array(0), fd_array_len(0), max_fd(-1), server_fd(0) {}
    ~EventSelector();

    void Add(FdHandler *h);
    void Remove(FdHandler *h);
    void SetServerFd(FdHandler *h);

    void Run();
};

////////////////////////////////////////

class Client;

class Server : public FdHandler
{

    enum game_step
    {
        not_started,
        started
    };
    struct item
    {
        Client *cl;
        item *next;
    };
    item *first;
    EventSelector *the_selector;
    Field *field;
    GameHandlerGemstone *handler;
    int snakes_count;
    game_step st;

    Server(int _fd, EventSelector *_the_selector,
           Field *_field,
           GameHandlerGemstone *_handler);

public:
    virtual ~Server();
    static Server *Start(int port, EventSelector *_the_selector,
                         Field *_field,
                         GameHandlerGemstone *_handler);

    void RemoveClient(Client *cl);

    virtual void Handle(bool r, bool w);
    void SendTo(int fd, const char *msg, int len);
    void StartGame() { st = started; }

private:
    void DrawAll();
};

class Client : public FdHandler
{
    friend class Server;
    char buf[buffersize];
    int buf_used;
    Snake *sn;

    Server *the_master;

public:
    Client(int _fd, Server *_the_master, Snake *_sn);
    virtual ~Client();

    virtual void Handle(bool r, bool w);
    void StringHandle(const char *msg);

private:
    Snake *GetSnake() { return sn; }
};

#endif