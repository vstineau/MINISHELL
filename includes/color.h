#ifndef COLOR_H
# define COLOR_H

//------------------------------
//REGULAR COLOR

# define BLACK "\001\033[0;30m\002"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"
//------------------------------

//------------------------------
// BOLD

# define B_BLACK "\033[1;30m"
# define B_RED "\001\e[1;31m\002"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[1;33m"
# define B_BLUE "\001\e[1;34m\002"
# define B_MAGENTA "\033[1;35m"
# define B_CYAN "\033[1;36m"
# define B_WHITE "\001\e[1;37m\002"
//------------------------------

//------------------------------
//UNDERLINE COLOR

# define U_BLACK "\033[4;30m"
# define U_RED "\033[4;31m"
# define U_GREEN "\033[4;32m"
# define U_YELLOW "\033[4;33m"
# define U_BLUE "\033[4;34m"
# define U_MAGENTA "\033[4;35m"
# define U_CYAN "\033[4;36m"
# define U_WHITE "\033[4;37m"
//------------------------------

//------------------------------
//BACKGROUD COLOR

# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"
//------------------------------

//------------------------------
//HIGHT INTENSITY COLOR (plus clair)

# define HI_BLACK "\033[90m"
# define HI_RED "\033[91m"
# define HI_GREEN "\033[92m"
# define HI_YELLOW "\033[93m"
# define HI_BLUE "\033[94m"
# define HI_MAGENTA "\033[95m"
# define HI_CYAN "\033[96m"
# define HI_WHITE "\033[97m"
//------------------------------

//------------------------------
//UNDERLINE HIGHT INTENSITY COLOR (plus clair)

# define UHI_BLACK "\033[4;90m"
# define UHI_RED "\033[4;91m"
# define UHI_GREEN "\033[4;92m"
# define UHI_YELLOW "\033[4;93m"
# define UHI_BLUE "\033[4;94m"
# define UHI_MAGENTA "\033[4;95m"
# define UHI_CYAN "\033[4;96m"
# define UHI_WHITE "\033[4;97m"
//------------------------------

//------------------------------
//BOLD HIGHT INTENSITY COLOR (plus clair)

# define BHI_BLACK "\033[1;90m"
# define BHI_RED "\033[1;91m"
# define BHI_GREEN "\033[1;92m"
# define BHI_YELLOW "\033[1;93m"
# define BHI_BLUE "\033[1;94m"
# define BHI_MAGENTA "\033[1;95m"
# define BHI_CYAN "\033[1;96m"
# define BHI_WHITE "\033[1;97m"
//------------------------------

//------------------------------
//HIGH INTENSITY BACKGROUND COLOR (plus clair)

# define HIBG_BLACK "\033[0;100m"
# define HIBG_RED "\033[0;101m"
# define HIBG_GREEN "\033[0;102m"
# define HIBG_YELLOW "\033[0;103m"
# define HIBG_BLUE "\033[0;104m"
# define HIBG_MAGENTA "\033[0;105m"
# define HIBG_CYAN "\033[0;106m"
# define HIBG_WHITE "\033[0;107m"
//------------------------------

#endif
