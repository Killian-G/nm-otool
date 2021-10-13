NAME := ft_nm

ifdef COUNT
T := $(shell $(MAKE) $(NAME) --no-print-directory -nrR PROGRESS="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)
PROGRESS = [`expr $C '*' 100 / $T`%%]
endif

PWD = $(shell pwd)
OS = $(shell uname)

# directories

SRC_DIR = src/
OBJ_DIR = obj/
HDR_DIR = include/

# libft

LFT_DIR = libft/
LFT = $(LFT_DIR)libft.a
LFT_HDRS = $(LFT_DIR)hdrs/
LFT_HDRS_FLAG = -I $(LFT_HDRS)
LFT_FLG = -L$(LFT_DIR) -lft

# Librairies

ifeq ($(OS), Linux)
	LIB_FLG = -Wl,-\( $(LFT_FLG) -Wl,-\)
	LIB_HDRS = $(LFT_HDRS_FLAG)
else
	LIB_FLG = $(LFT_FLG)
	LIB_HDRS = $(LFT_HDRS_FLAG)
endif

# Sources

SRCDIR_OPTION = option/

SRCS_OPTION =	numeric_sort_option.c   \
                reverse_sort_option.c   \
                no_sort_option.c

SRCS =	$(addprefix $(SRCDIR_OPTION), $(SRCS_OPTION))   \
        env.c	\
		main.c  \
		args_parser.c   \
		print_symbol.c

# Headers

HDRS =	ft_nm.h

# Final files

OBJDIRS :=	$(OBJ_DIR)  \
            $(OBJ_DIR)$(SRCDIR_OPTION)

OBJS :=	$(addprefix $(OBJ_DIR),$(SRCS:.c=.o))

SRCS :=	$(addprefix $(SRC_DIR),$(SRCS))

HDRS :=	$(addprefix $(HDR_DIR),$(HDRS))

FULL_HDRS :=	-I $(HDR_DIR)	\
				$(LIB_HDRS)

# Display

HIDE_CURSOR := \e[?25l
SHOW_CURSOR := \e[?25h
CURSOR_LEFT := \e[1000D
ERASE_ENDLINE := \e[K
ERASE_FULLLINE := \e[2K

# Global variable (compiler / shell)

CC = clang
RAN = ar rcs
RM = /bin/rm -rf
PRINT = printf
CFLAGS = -Wall -Wextra -Werror

# Flags

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

# -fsanitize=address -fsanitize=undefined

ifeq ($(FS), 1)
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer
endif

ifneq ($(OPTI), 0)
	CFLAGS += -O3
endif

# Rules

all: premake

debug:
	$(MAKE) OPTI=0 FS=1 DEBUG=1

premake: $(OBJDIRS) libmake_libft
	$(MAKE) $(NAME) --no-print-directory COUNT=1 OPTI=$(OPTI) FS=$(FS) DEBUG=$(DEBUG)

libmake_libft:
	cd $(LFT_DIR) && $(MAKE) OPTI=$(OPTI) FS=$(FS) DEBUG=$(DEBUG)

libclean:
	cd $(LFT_DIR) && $(MAKE) clean

libfclean:
	cd $(LFT_DIR) && $(MAKE) fclean

test: libmake $(HDRS) $(LFT)
	$(CC) $(CFLAGS) -o test test.c $(FULL_HDRS) $(LIB_FLG)

$(OBJDIRS):
	mkdir -p $@

# -lstdc++ -lunwind -DWITHGPERFTOOLS /usr/lib/libprofiler.*

$(NAME): $(OBJS) $(HDRS) $(LFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_FLG)
	@$(PRINT) "$(ERASE_FULLLINE)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n$(SHOW_CURSOR)" "$(NAME)" "Compilation $@"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDRS) $(LFT)
	$(CC) $(CFLAGS) -c $(FULL_HDRS) -o $@ $<
	@$(PRINT) "$(HIDE_CURSOR)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m$(PROGRESS)\033[0m$(ERASE_ENDLINE)$(CURSOR_LEFT)" "$(NAME)" "Compilation"

clean: libclean
	@@$(RM) $(OBJDIRS)
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "$(NAME)" "Cleaning objs"

clean2:
	@$(RM) $(OBJDIRS)
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "$(NAME)" "Cleaning objs"

fclean: clean2 libfclean
	@$(RM) $(NAME)
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "$(NAME)" "Cleaning $(NAME)"

re: fclean all

show_cursor:
	@printf "\033[38;2;0;255;0mThe cursor just came back ...\033[0m$(SHOW_CURSOR)\n"

.PHONY: all clean clean2 fclean re libmake libclean libfclean sdl2_brew sdl2_prebuild sdl2_postbuild sdl2_build debug show_cursor test

#asd