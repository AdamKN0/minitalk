CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS_C =  client.c utils.c
SRCS_S =  server.c utils.c
SRCS_BC =  client_bonus.c utils_bonus.c
SRCS_BS =  server_bonus.c utils_bonus.c

SERVER_NAME= server
CLIENT_NAME= client
B_SERVER_NAME= server_bonus
B_CLIENT_NAME= client_bonus

OBJS_C= $(SRCS_C:.c=.o)
OBJS_S= $(SRCS_S:.c=.o)
OBJS_BC= $(SRCS_BC:.c=.o)
OBJS_BS= $(SRCS_BS:.c=.o)

all:    $(SERVER_NAME) $(CLIENT_NAME)


bonus:  $(B_SERVER_NAME) $(B_CLIENT_NAME)

$(SERVER_NAME): $(OBJS_S) minitalk.h
	$(CC) $(CFLAGS) $(OBJS_S) -o $(SERVER_NAME)

$(CLIENT_NAME): $(OBJS_C) minitalk.h
	$(CC) $(CFLAGS) $(OBJS_C) -o $(CLIENT_NAME)

$(B_SERVER_NAME): $(OBJS_BS) minitalk_bonus.h
	$(CC) $(CFLAGS) $(OBJS_BS) -o $(B_SERVER_NAME)

$(B_CLIENT_NAME): $(OBJS_BC) minitalk_bonus.h
	$(CC) $(CFLAGS) $(OBJS_BC) -o $(B_CLIENT_NAME)

clean:
	$(RM) $(OBJS_C) $(OBJS_S) $(OBJS_BC) $(OBJS_BS)

fclean: clean
	$(RM) $(SERVER_NAME) $(CLIENT_NAME) $(B_SERVER_NAME) $(B_CLIENT_NAME)
	
re: fclean all
