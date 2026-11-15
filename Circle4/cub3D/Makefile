NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
CPPFLAGS = -I. -Iincludes -Ilibft -Iminilibx-linux -O3

GREEN = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m
BOLD = \033[1m

SRC_DIR = srcs
BUILD_DIR = build
MANDA_BUILD = $(BUILD_DIR)/mandatory
BONUS_BUILD = $(BUILD_DIR)/bonus

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

ALL_SRCS = $(shell find $(SRC_DIR) -maxdepth 1 -type f -name '*.c' | sort -V)
MANDA_SRCS = $(filter-out %_bonus.c,$(ALL_SRCS))
BONUS_SRCS = $(ALL_SRCS)
HEADERS = $(sort $(wildcard includes/*.h) $(wildcard libft/*.h) \
	$(wildcard minilibx-linux/*.h))

MANDA_OBJS = $(MANDA_SRCS:$(SRC_DIR)/%.c=$(MANDA_BUILD)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(SRC_DIR)/%.c=$(BONUS_BUILD)/%.o)

MANDA_DEPS = $(MANDA_OBJS:.o=.d)
BONUS_DEPS = $(BONUS_OBJS:.o=.d)

LIBFT_SRCS = $(sort $(wildcard $(LIBFT_DIR)/*.c))
LIBFT_HEADERS = $(sort $(wildcard $(LIBFT_DIR)/*.h))

all: mandatory

$(NAME): mandatory

$(BONUS_NAME): bonus

mandatory:
	@clear 2>/dev/null || true
	@if [ -d "$(BONUS_BUILD)" ] || [ -f "$(BONUS_NAME)" ]; then \
		echo "$(YELLOW)Removing bonus build before mandatory build...$(RESET)"; \
		rm -rf $(BONUS_BUILD); \
		rm -f $(BONUS_NAME); \
	fi
	@to_compile=$$(for src in $(MANDA_SRCS); do \
		obj=$$src; \
		obj=$${obj#$(SRC_DIR)/}; \
		obj=$(MANDA_BUILD)/$${obj%.c}.o; \
		if [ ! -f "$$obj" ] || [ "$$src" -nt "$$obj" ] \
			|| [ "Makefile" -nt "$$obj" ] \
			|| [ -n "$$(find includes libft minilibx-linux -type f -name '*.h' -newer "$$obj" 2>/dev/null | head -1)" ]; then \
			echo "$$src"; \
		fi; \
	done | wc -l); \
	echo 0 > /tmp/.manda_count; \
	echo $$to_compile > /tmp/.manda_total; \
	echo "$(BOLD)$(BLUE)Starting compilation for '$(NAME)' (mandatory)$(RESET)"; \
	if [ $$to_compile -gt 0 ]; then \
		echo "$(CYAN)Files to compile: $$to_compile$(RESET)"; \
	fi
	@$(MAKE) --no-print-directory build_manda

bonus:
	@clear 2>/dev/null || true
	@if [ -d "$(MANDA_BUILD)" ] || [ -f "$(NAME)" ]; then \
		echo "$(YELLOW)Removing mandatory build before bonus build...$(RESET)"; \
		rm -rf $(MANDA_BUILD); \
		rm -f $(NAME); \
	fi
	@to_compile=$$(for src in $(BONUS_SRCS); do \
		obj=$$src; \
		obj=$${obj#$(SRC_DIR)/}; \
		obj=$(BONUS_BUILD)/$${obj%.c}.o; \
		if [ ! -f "$$obj" ] || [ "$$src" -nt "$$obj" ] \
			|| [ "Makefile" -nt "$$obj" ] \
			|| [ -n "$$(find includes libft minilibx-linux -type f -name '*.h' -newer "$$obj" 2>/dev/null | head -1)" ]; then \
			echo "$$src"; \
		fi; \
	done | wc -l); \
	echo 0 > /tmp/.bonus_count; \
	echo $$to_compile > /tmp/.bonus_total; \
	echo "$(BOLD)$(BLUE)Starting compilation for '$(BONUS_NAME)' (bonus)$(RESET)"; \
	if [ $$to_compile -gt 0 ]; then \
		echo "$(CYAN)Files to compile: $$to_compile$(RESET)"; \
	fi
	@$(MAKE) --no-print-directory build_bonus

build_manda: $(MANDA_OBJS) $(LIBFT) $(MLX)
	@if [ ! -f $(NAME) ] || [ -n "$$(find $(MANDA_BUILD) -name '*.o' -newer $(NAME) 2>/dev/null | head -1)" ] \
		|| [ "$(LIBFT)" -nt "$(NAME)" ] || [ "$(MLX)" -nt "$(NAME)" ]; then \
		echo "\n$(BOLD)$(GREEN)✓ Compilation completed for '$(NAME)' (mandatory)$(RESET)"; \
		echo "$(CYAN)Linking...$(RESET)"; \
		$(CC) $(CFLAGS) -o $(NAME) $(MANDA_OBJS) $(LIBFT) $(MLX_FLAGS); \
		echo "$(BOLD)$(GREEN)✓ Build successful!$(RESET)"; \
	else \
		echo "$(YELLOW)Nothing to update for '$(NAME)' (mandatory).$(RESET)"; \
	fi

build_bonus: $(BONUS_OBJS) $(LIBFT) $(MLX)
	@if [ ! -f $(BONUS_NAME) ] || [ -n "$$(find $(BONUS_BUILD) -name '*.o' -newer $(BONUS_NAME) 2>/dev/null | head -1)" ] \
		|| [ "$(LIBFT)" -nt "$(BONUS_NAME)" ] || [ "$(MLX)" -nt "$(BONUS_NAME)" ]; then \
		echo "\n$(BOLD)$(GREEN)✓ Compilation completed for '$(BONUS_NAME)' (bonus)$(RESET)"; \
		echo "$(CYAN)Linking...$(RESET)"; \
		$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFT) $(MLX_FLAGS); \
		echo "$(BOLD)$(GREEN)✓ Build successful!$(RESET)"; \
	else \
		echo "$(YELLOW)Nothing to update for '$(BONUS_NAME)' (bonus).$(RESET)"; \
	fi

$(MANDA_BUILD)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile | $(MANDA_BUILD)
	@mkdir -p $(dir $@)
	@current=$$(cat /tmp/.manda_count 2>/dev/null || echo 0); \
	total=$$(cat /tmp/.manda_total 2>/dev/null || echo 1); \
	if [ $$total -le 0 ]; then total=1; fi; \
	current=$$((current + 1)); \
	echo $$current > /tmp/.manda_count; \
	percent=$$((current * 100 / total)); \
	bar_len=$$((percent / 2)); \
	printf "\r$(GREEN)["; \
	for i in $$(seq 1 $$bar_len); do printf "█"; done; \
	for i in $$(seq $$((bar_len + 1)) 50); do printf " "; done; \
	printf "]$(RESET) $(CYAN)%3d%%$(RESET) $(YELLOW)(%3d/%-3d)$(RESET) %-30s" \
		$$percent $$current $$total "$(notdir $<)"
	@if ! $(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@ 2>&1; then \
		printf "\n$(RED)$(BOLD)✗ Compilation failed for $(notdir $<)$(RESET)\n"; \
		exit 1; \
	fi

$(BONUS_BUILD)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile | $(BONUS_BUILD)
	@mkdir -p $(dir $@)
	@current=$$(cat /tmp/.bonus_count 2>/dev/null || echo 0); \
	total=$$(cat /tmp/.bonus_total 2>/dev/null || echo 1); \
	if [ $$total -le 0 ]; then total=1; fi; \
	current=$$((current + 1)); \
	echo $$current > /tmp/.bonus_count; \
	percent=$$((current * 100 / total)); \
	bar_len=$$((percent / 2)); \
	printf "\r$(GREEN)["; \
	for i in $$(seq 1 $$bar_len); do printf "█"; done; \
	for i in $$(seq $$((bar_len + 1)) 50); do printf " "; done; \
	printf "]$(RESET) $(CYAN)%3d%%$(RESET) $(YELLOW)(%3d/%-3d)$(RESET) %-30s" \
		$$percent $$current $$total "$(notdir $<)"
	@if ! $(CC) $(CFLAGS) $(CPPFLAGS) -DBONUS -MMD -MP -c $< -o $@ 2>&1; then \
		printf "\n$(RED)$(BOLD)✗ Compilation failed for $(notdir $<)$(RESET)\n"; \
		exit 1; \
	fi

$(LIBFT): $(LIBFT_SRCS) $(LIBFT_HEADERS) $(LIBFT_DIR)/Makefile
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX): $(wildcard $(MLX_DIR)/*.c) $(wildcard $(MLX_DIR)/*.h) $(MLX_DIR)/Makefile
	@$(MAKE) -C $(MLX_DIR)

$(MANDA_BUILD):
	@mkdir -p $@

$(BONUS_BUILD):
	@mkdir -p $@

clean:
	@clear 2>/dev/null || true
	@echo "$(YELLOW)Cleaning object files for '$(NAME)' and '$(BONUS_NAME)'...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(BUILD_DIR)
	@echo "$(GREEN)✓ Clean complete$(RESET)"

fclean: clean
	@clear 2>/dev/null || true
	@echo "$(YELLOW)Cleaning all generated files for '$(NAME)' and '$(BONUS_NAME)'...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "$(GREEN)✓ Full clean complete$(RESET)"

re: fclean all

-include $(MANDA_DEPS) $(BONUS_DEPS)

.PHONY: all mandatory bonus build_manda build_bonus clean fclean re
