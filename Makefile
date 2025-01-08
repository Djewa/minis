NAME    = minishell
CC      = cc
CFLAGS  = -Wextra -Wall -Werror -g -I includes/ -I libft/
LIBFT   = ./libft/libft.a
HEADERS = minishell.h

# รายการไฟล์ .c ที่ต้องคอมไพล์
MAIN    = main.c process.c heredoc.c error_func.c utils.c system.c sub_system.c rules.c signal.c file_err.c cmd_err.c
BUILTINS = exit.c env.c unset.c cd_cmd.c
HANDLE = check_cmd.c syntax.c syntax_utils.c check_quote.c

SRCS = $(addsuffix , $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix , $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix , $(addprefix srcs/handle/, $(HANDLE))) \

OBJS    = $(SRCS:.c=.o)

# เป้าหมายหลัก
all: $(NAME)

# สั่งให้เข้าไปที่โฟลเดอร์ libft และทำการคอมไพล์
# libft:
# 	@make -C $(LIBFT)

# คอมไพล์โปรเจ็กต์หลัก (minishell) จากไฟล์ .o
# $(NAME): $(OBJS)
# 	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME) $(LIBFT)/libft.a -lreadline

$(NAME): $(OBJS)
	@make -C libft/
	@echo "\e[0;36mCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@echo "Done!"

# คอมไพล์ไฟล์ .c เป็น .o
%.o: %.c $(LIBFT)/libft.h
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

# ทำความสะอาดไฟล์ .o
clean:
	@make clean -C libft/
	@rm -f $(OBJS)

# ลบไฟล์ที่คอมไพล์แล้วในโฟลเดอร์ libft และโปรเจ็กต์หลัก
fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

# ทำใหม่ทั้งหมด
re: fclean all

.PHONY: all clean fclean re libft
