#ifndef GAMEINIT_HPP_SENTRY
#define GAMEINIT_HPP_SENTRY

class GameInit {
	enum {
		max_argc = 11,

		std_port = 8808,

    	std_width = 100,
    	std_height = 40,
    	std_food_count = 15
	};
	
	int argc;
	const char **argv;	

public:
	GameInit(int _argc, const char **_argv) : argc(_argc), argv(_argv) {}
	~GameInit() {}

	int Start();

private:
	bool IsOneOfArgv(const char *argv[6], const char *arg, 
					 int argc, int *matched_argv_idx);
	bool HandleArgv(int argv_idx, int matched_argv, 
					int *num_args, const char **ip);
	void WriteHelp();
};

#endif
