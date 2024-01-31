# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 13:00:49 by pborrull          #+#    #+#              #
#    Updated: 2024/01/23 12:28:30 by pborrull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER := server
CLIENT := client

GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED = \033[1;31m
MAGENTA = \033[1;35m
BLUE = \033[38;5;75m
ORIGINAL = \033[0m

CFLAGS := -Wall -Werror -Wextra -MMD

PRINTF := printf/

SOURCE := server.c client.c

SOURCE_BONUS := server_bonus.c client_bonus.c

OBJS := $(SOURCE:.c=.o)

DEPS := $(SOURCE:.c=.d)

OBJS_BONUS := $(SOURCE_BONUS:.c=.o)

DEPS_BONUS := $(SOURCE_BONUS:.c=.d)

.SILENT:

all:
	@make -C $(PRINTF) > /dev/null
	@make $(SERVER) 
	@make $(CLIENT) 

$(SERVER): $(OBJS) Makefile 
	@$(CC) $(CFLAGS) server.c $(PRINTF)libftprintf.a -o $(SERVER) > /dev/null
	@echo  "$(GREEN)[OK]       $(YELLOW)Server Compiled$(ORIGINAL)"
	
$(CLIENT): $(OBJS) Makefile
	@$(CC) $(CFLAGS) client.c  $(PRINTF)libftprintf.a -o $(CLIENT) > /dev/null
	@echo  "$(GREEN)[OK]       $(YELLOW)Client Compiled$(ORIGINAL)"

bonus: $(OBJS_BONUS) Makefile
	@make -C $(PRINTF) > /dev/null
	@$(CC) $(CFLAGS) server_bonus.c $(PRINTF)libftprintf.a -o $(SERVER) 
	@$(CC) $(CFLAGS) client_bonus.c  $(PRINTF)libftprintf.a -o $(CLIENT)
	@echo  "$(GREEN)[OK]       $(YELLOW)BONUS Compiled$(ORIGINAL)"

clean:
	@make clean -C $(PRINTF) > /dev/null
	@rm -f $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS)
	@echo "$(RED)[OK]       $(BLUE)All Clean$(ORIGINAL)"

fclean: clean
	@make fclean -C $(PRINTF) > /dev/null
	@rm -f $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS) $(SERVER) $(CLIENT) > /dev/null
	@echo  "$(RED)[OK]       $(MAGENTA)All Very Clean$(ORIGINAL)"

re: fclean all

-include $(DEPS) $(DEPS_BONUS)

.PHONY: all make clean fclean bonus re
