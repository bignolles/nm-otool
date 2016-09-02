OTOOL =				ft_otool
NM =				ft_nm
OTOOL_DIR =			./otool
NM_DIR =			./nm
OTOOL_BUILD =		$(OTOOL_DIR)/ft_otool
NM_BUILD =			$(NM_DIR)/ft_nm
LIBFT_DIR =			./libft

all: $(OTOOL_BUILD) $(NM_BUILD)

clean: otool_clean nm_clean

fclean: libft_fclean otool_fclean nm_fclean

re: fclean $(OTOOL_BUILD) $(NM_BUILD)

$(OTOOL_BUILD):
	make -C $(OTOOL_DIR)
	cp $(OTOOL_BUILD) .

otool_clean:
	make -C $(OTOOL_DIR) clean

otool_fclean:
	make -C $(OTOOL_DIR) fclean
	rm -f ./ft_otool

otool_re :make -C $(OTOOL_DIR) re

$(NM_BUILD):
	make -C $(NM_DIR)
	cp $(NM_BUILD) .

nm_clean:
	make -C $(NM_DIR) clean

nm_fclean:
	make -C $(NM_DIR) fclean
	rm -f ./ft_nm

nm_re :make -C $(NM_DIR) re

libft_fclean:
	make -C $(LIBFT_DIR) fclean

.PHONY:
