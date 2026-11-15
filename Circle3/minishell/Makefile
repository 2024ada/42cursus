NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

GREEN = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m
BOLD = \033[1m

MANDA_DIR = mandatory
BONUS_DIR = bonus

MANDA_BUILD = $(MANDA_DIR)/build
BONUS_BUILD = $(BONUS_DIR)/build

MANDA_SRCS = $(shell find $(MANDA_DIR)/srcs -name "*.c" 2>/dev/null)
BONUS_SRCS = $(shell find $(BONUS_DIR)/srcs -name "*.c" 2>/dev/null)

MANDA_OBJS = $(MANDA_SRCS:$(MANDA_DIR)/srcs/%.c=$(MANDA_BUILD)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/srcs/%.c=$(BONUS_BUILD)/%.o)

MANDA_TOTAL = $(words $(MANDA_SRCS))
BONUS_TOTAL = $(words $(BONUS_SRCS))

MANDA_INC = -I $(MANDA_DIR)/include
BONUS_INC = -I $(BONUS_DIR)/include

all: mandatory

mandatory:
	@clear
	@if [ -d "$(BONUS_BUILD)" ]; then \
		rm -rf $(BONUS_BUILD); \
		rm -f $(NAME); \
	fi
	@to_compile=$$(for src in $(MANDA_SRCS); do \
		obj=$$(echo $$src | sed 's|$(MANDA_DIR)/srcs/|$(MANDA_BUILD)/|;s|\.c$$|.o|'); \
		if [ ! -f "$$obj" ] || [ "$$src" -nt "$$obj" ]; then echo "$$src"; fi; \
	done | wc -l); \
	echo 0 > /tmp/.manda_count; \
	echo $$to_compile > /tmp/.manda_total; \
	echo "$(BOLD)$(BLUE)Starting compilation for '$(NAME)' (mandatory)$(RESET)"; \
	if [ $$to_compile -gt 0 ]; then \
		echo "$(CYAN)Files to compile: $$to_compile$(RESET)"; \
	fi
	@$(MAKE) --no-print-directory build_manda

bonus:
	@clear
	@if [ -d "$(MANDA_BUILD)" ]; then \
		rm -rf $(MANDA_BUILD); \
		rm -f $(NAME); \
	fi
	@to_compile=$$(for src in $(BONUS_SRCS); do \
		obj=$$(echo $$src | sed 's|$(BONUS_DIR)/srcs/|$(BONUS_BUILD)/|;s|\.c$$|.o|'); \
		if [ ! -f "$$obj" ] || [ "$$src" -nt "$$obj" ]; then echo "$$src"; fi; \
	done | wc -l); \
	echo 0 > /tmp/.bonus_count; \
	echo $$to_compile > /tmp/.bonus_total; \
	echo "$(BOLD)$(BLUE)Starting compilation for '$(NAME)' (bonus)$(RESET)"; \
	if [ $$to_compile -gt 0 ]; then \
		echo "$(CYAN)Files to compile: $$to_compile$(RESET)"; \
	fi
	@$(MAKE) --no-print-directory build_bonus

build_manda: $(MANDA_OBJS)
	@if [ ! -f $(NAME) ] || [ -n "$$(find $(MANDA_BUILD) -name '*.o' -newer $(NAME) 2>/dev/null | head -1)" ]; then \
		echo "\n$(BOLD)$(GREEN)✓ Compilation completed for '$(NAME)' (mandatory)$(RESET)"; \
		echo "$(CYAN)Linking...$(RESET)"; \
		$(CC) $(CFLAGS) -o $(NAME) $(MANDA_OBJS) -lreadline; \
		echo "$(BOLD)$(GREEN)✓ Build successful!$(RESET)"; \
	else \
		echo "$(YELLOW)Nothing to update for '$(NAME)' (mandatory).$(RESET)"; \
	fi

build_bonus: $(BONUS_OBJS)
	@if [ ! -f $(NAME) ] || [ -n "$$(find $(BONUS_BUILD) -name '*.o' -newer $(NAME) 2>/dev/null | head -1)" ]; then \
		echo "\n$(BOLD)$(GREEN)✓ Compilation completed for '$(NAME)' (bonus)$(RESET)"; \
		echo "$(CYAN)Linking...$(RESET)"; \
		$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS) -lreadline; \
		echo "$(BOLD)$(GREEN)✓ Build successful!$(RESET)"; \
	else \
		echo "$(YELLOW)Nothing to update for '$(NAME)' (bonus).$(RESET)"; \
	fi

$(MANDA_BUILD)/%.o: $(MANDA_DIR)/srcs/%.c
	@mkdir -p $(dir $@)
	@current=$$(cat /tmp/.manda_count 2>/dev/null || echo 0); \
	total=$$(cat /tmp/.manda_total 2>/dev/null || echo 1); \
	current=$$((current + 1)); \
	echo $$current > /tmp/.manda_count; \
	percent=$$((current * 100 / total)); \
	bar_len=$$((percent / 2)); \
	printf "\r$(GREEN)["; \
	for i in $$(seq 1 $$bar_len); do printf "█"; done; \
	for i in $$(seq $$((bar_len + 1)) 50); do printf " "; done; \
	printf "]$(RESET) $(CYAN)%3d%%$(RESET) $(YELLOW)(%3d/%-3d)$(RESET) %-30s" \
		$$percent $$current $$total "$(notdir $<)"
	@if ! $(CC) $(CFLAGS) $(MANDA_INC) -c $< -o $@ 2>&1; then \
		printf "\n$(RED)$(BOLD)✗ Compilation failed for $(notdir $<)$(RESET)\n"; \
		exit 1; \
	fi

$(BONUS_BUILD)/%.o: $(BONUS_DIR)/srcs/%.c
	@mkdir -p $(dir $@)
	@current=$$(cat /tmp/.bonus_count 2>/dev/null || echo 0); \
	total=$$(cat /tmp/.bonus_total 2>/dev/null || echo 1); \
	current=$$((current + 1)); \
	echo $$current > /tmp/.bonus_count; \
	percent=$$((current * 100 / total)); \
	bar_len=$$((percent / 2)); \
	printf "\r$(GREEN)["; \
	for i in $$(seq 1 $$bar_len); do printf "█"; done; \
	for i in $$(seq $$((bar_len + 1)) 50); do printf " "; done; \
	printf "]$(RESET) $(CYAN)%3d%%$(RESET) $(YELLOW)(%3d/%-3d)$(RESET) %-30s" \
		$$percent $$current $$total "$(notdir $<)"
	@if ! $(CC) $(CFLAGS) $(BONUS_INC) -c $< -o $@ 2>&1; then \
		printf "\n$(RED)$(BOLD)✗ Compilation failed for $(notdir $<)$(RESET)\n"; \
		exit 1; \
	fi

clean:
	@clear
	@echo "$(YELLOW)Cleaning object files for '$(NAME)'...$(RESET)"
	@rm -rf $(MANDA_BUILD) $(BONUS_BUILD)
	@echo "$(GREEN)✓ Clean complete$(RESET)"

fclean:
	@clear
	@echo "$(YELLOW)Cleaning all generated files for '$(NAME)'...$(RESET)"
	@rm -rf $(MANDA_BUILD) $(BONUS_BUILD)
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean complete$(RESET)"

re: fclean all

.PHONY: all mandatory bonus clean fclean re