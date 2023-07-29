
NAME = minishell
CC = gcc

CFLAGS = -Wall -Werror -Wextra -g
ifeq ($(shell uname), Linux)

LIBRARIES = $(FT_LNK) -lreadline
INCLUDES = $(FT_INC)

endif

ifeq ($(shell uname), Darwin)

LIBRARIES = $(FT_LNK) $(READ_LNK)
INCLUDES = $(FT_INC) $(READ_INC)

endif
HEADER = ./header
SRCDIR = src/

LIBFT = $(LIBFT_DIRECTORY)/libft.a
LIBFT_DIRECTORY = ./libft
FT_INC	= -I ./libft/
FT_LNK	= ./libft/libft.a
READ_LNK = -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
READ_INC = -I $(HOME)/goinfre/.brew/opt/readline/include/
OBJDIR = build/


SRCS := main.c parser.c list_input.c run_commands.c run_pipes.c error_handling.c \
		handle_pipes.c init_pipex.c pipe_util.c split_pipex.c run_single_com.c \
		utilities.c parse_redirect.c parse_com_line.c file_handle.c \
		child.c redirection.c list_coms.c here_doc.c list_redirect.c \
		signal.c quote_checker.c builtins_utils.c cleanup.c ft_export_utils.c\
		ft_cd.c ft_export.c ft_unset.c ft_echo.c ft_env.c ft_pwd.c \
		parse_utilities.c expand_env.c replace_word.c env_list.c \
		ft_exit.c quote_handling.c list_words.c replace_word_util.c prompt.c


OBJS := $(SRCS:.c=.o)
OBJECTS_PREFIXED := $(addprefix $(OBJDIR), $(OBJS))

.PHONY: test

$(NAME): $(LIBFT) $(OBJECTS_PREFIXED) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJECTS_PREFIXED) $(LIBRARIES) -I$(HEADER) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_PREFIXED): build/%.o : src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(HEADER) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) all -sC $(LIBFT_DIRECTORY)


all: $(NAME)

clean:
	@cd $(LIBFT_DIRECTORY) && make clean
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIBFT_DIRECTORY)/libft.a
	rm -f $(NAME)

re: fclean all

test: CFLAGS+= -fsanitize=address -fsanitize=leak -g

test: re