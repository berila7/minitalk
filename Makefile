SERVER_NAME		=	server
CLIENT_NAME		=	client
SERVER_BONUS	=	server_bonus
CLIENT_BONUS	=	client_bonus

CC				=	cc
LIBFT_DIR		=	libft
FT_PRINTF_DIR	=	ft_printf
FLAGS			=	-Wall -Wextra -Werror
LIBFT			=	$(LIBFT_DIR)/libft.a
FT_PRINTF		=	$(FT_PRINTF_DIR)/libftprintf.a

SERVER_SRCS		=	mandatory/server.c
CLIENT_SRCS		=	mandatory/client.c

BONUS_S_SRCS	=	bonus/server_bonus.c
BONUS_C_SRCS	=	bonus/client_bonus.c

SERVER_OBJS		=	$(SERVER_SRCS:.c=.o)
CLIENT_OBJS		=	$(CLIENT_SRCS:.c=.o)

BONUS_S_OBJS	=	$(BONUS_S_SRCS:.c=.o)
BONUS_C_OBJS	=	$(BONUS_C_SRCS:.c=.o)

all: $(LIBFT_DIR) $(FT_PRINTF_DIR) $(SERVER_NAME) $(CLIENT_NAME)

$(LIBFT_DIR):
	@make -C $(LIBFT_DIR)

$(FT_PRINTF_DIR):
	@make -C $(FT_PRINTF_DIR)

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(FLAGS) $(SERVER_OBJS) $(LIBFT) $(FT_PRINTF) -o $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(FLAGS) $(CLIENT_OBJS) $(LIBFT) $(FT_PRINTF) -o $(CLIENT_NAME)

bonus: $(LIBFT_DIR) $(FT_PRINTF_DIR) $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(BONUS_S_OBJS)
	$(CC) $(FLAGS) $(BONUS_S_OBJS) $(LIBFT) $(FT_PRINTF) -o $(SERVER_BONUS)

$(CLIENT_BONUS): $(BONUS_C_OBJS)
	$(CC) $(FLAGS) $(BONUS_C_OBJS) $(LIBFT) $(FT_PRINTF) -o $(CLIENT_BONUS)

mandatory/%server.o: mandatory/%server.c $(FT_PRINTF) $(LIBFT) includes/minitalk.h
	$(CC) $(FLAGS) -c $< -o $@

mandatory/%client.o: mandatory/%client.c $(FT_PRINTF) $(LIBFT) includes/minitalk.h
	$(CC) $(FLAGS) -c $< -o $@

bonus/%server_bonus.o: bonus/%server_bonus.c $(FT_PRINTF) $(LIBFT) includes/minitalk_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

bonus/%client_bonus.o: bonus/%client_bonus.c $(FT_PRINTF) $(LIBFT) includes/minitalk_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(BONUS_S_OBJS) $(BONUS_C_OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)
	rm -f $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

.PHONY: $(LIBFT_DIR) $(FT_PRINTF_DIR)