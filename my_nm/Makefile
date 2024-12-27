SRC = src/main.c \
        src/init_struct.c \
		src/new_bits.c \

CC        = gcc

OBJS    = $(SRC:.c=.o)

EXEC    = my_nm

all: ${EXEC}

${EXEC}: ${OBJS}
	@echo -e "\033[1;33m\tC O M P I L I N G   P R O G\033[0m"
	@${CC} -g -o ${EXEC} ${OBJS}&& \
		(echo -e "\033[1;32m\t\t✅ $< \033\033[0m\n")

clean:
	@echo -e "\033[1;33m\tC L E A N I N G   P R O G\033[0m"
	@echo -e "\033[1;31m\t\t🏎️  KA-CHOW 🏎️\033[0m"
	rm -f ${OBJS}

fclean: clean
	rm -f ${EXEC}

re: fclean all

.PHONY: all clean fclean re
