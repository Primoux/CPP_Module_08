.PHONY : all re fclean clean run



NAME			= easyfind

MAKEFLAGS		+= -j $$(nproc)

CC				= c++
CFLAGS			= -std=c++98 -Wall -Wextra -Werror -g3
DEPS			= -MMD -MP

OBJ_DIR			= .build/
INCLUDE_DIR		= -Iinclude/
INCLUDES 		= $(INCLUDE_DIR)

SRCS			=	source/main.cpp


OBJS			= $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRCS))
DEPENDENCIES	= $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEPS) -c $< -o $@

-include $(DEPENDENCIES)

run: all
	./$(NAME)

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re: fclean
	$(MAKE) all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
