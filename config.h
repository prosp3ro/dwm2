#include <X11/X.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const unsigned int gappih    = 7;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 7;       /* vert inner gap between windows */
static const unsigned int gappoh    = 7;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 7;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;        /* 0 means no systray */

static char *fonts[] = { 
    "monospace:size=10",
    "NotoColorEmoji:pixelsize=11:antialias=true:autohint=true"
};

static char *colors[][3] = {
    /*               fg          bg          border   */
    [SchemeNorm] = { "#bbbbbb",  "#222222",  "#000000" },
    [SchemeSel]  = { "#eeeeee",  "#005577",  "#770000" },
    [SchemeHid]  = { "#005577",  "#222222",  "#005577" },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    /* class                    instance        title      tags mask   isfloating   monitor */
    { "Gimp",                   NULL,           NULL,      0,          1,           -1 },
    { "Tor Browser",            NULL,           NULL,      0,          1,           -1 },
    { "brave",                  NULL,           NULL,      0,          1,           -1 },
    { "B1",                     NULL,           NULL,      1,          0,           -1 },
    { "B2",                     NULL,           NULL,      1 << 2,     0,           -1 },
    { "Nsxiv",                  NULL,           NULL,      0,          1,           -1 },
    { "Blueman-manager",        NULL,           NULL,      0,          1,           -1 },
    { "Wpa_gui",                NULL,           NULL,      0,          1,           -1 },
    { "mpv",                    NULL,           NULL,      0,          1,           -1 },
    { "stacer",                 NULL,           NULL,      0,          1,           -1 },
    { "pop-up",                 NULL,           NULL,      0,          1,           -1 },
    { "Gpick",                  NULL,           NULL,      0,          1,           -1 },
    { "pavucontrol",            NULL,           NULL,      0,          1,           -1 },
    { "YouTube Music",          NULL,           NULL,      1 << 6,     0,           -1 },
    { "firefox",                NULL,           NULL,      1 << 6,     0,           -1 },
    { "obsidian",               NULL,           NULL,      1 << 8,     0,           -1 },
    { "LibreWolf",              NULL,           NULL,      1 << 7,     0,           -1 },
    { "Signal",                 NULL,           NULL,      1 << 7,     0,           -1 },
    { "Chromium",               NULL,           NULL,      1 << 2,     0,           -1 },
    { "Ferdium",                NULL,           NULL,      1 << 3,     0,           -1 },
    { "st-dev",                 NULL,           NULL,      1 << 1,     0,           -1 },
    // { "chatterino",             "chatterino",   NULL,      0,          1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* first entry is default */
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile    },
	// { "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                            KEY,            view,                 {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,                  KEY,            tag,                  {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, NULL };
static const char scratchpadname[] = "scratch";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", "-e", "ses", scratchpadname, NULL };

static const Key keys[] = {
    /* modifier              key                 function             argument */
	{ MODKEY,                XK_j,               focusstackvis,       {.i = +1 } },
	{ MODKEY,                XK_k,               focusstackvis,       {.i = -1 } },
    { MODKEY,                XK_h,               setmfact,            {.f = -0.05} },
    { MODKEY,                XK_l,               setmfact,            {.f = +0.05} },
    { MODKEY,                XK_d,               spawn,               {.v = dmenucmd } },
    { MODKEY|ShiftMask,      XK_d,	             spawn,               SHCMD("keepmenu") },
    { MODKEY,                XK_o,               spawn,               {.v = (const char*[]){ "st", "-c", "st-dev", "-t", "tmux", "-e", "ses", "main", NULL } } },
	{ MODKEY|ShiftMask,      XK_o,               togglescratch,       {.v = scratchpadcmd } },
    { MODKEY,                XK_Return,          spawn,               {.v = (const char*[]){ "st", NULL } } },
    { MODKEY,                XK_b,               togglebar,           {0} },
    { MODKEY,                XK_q,               killclient,          {0} },
    { MODKEY|ShiftMask,      XK_q,               quit,                {0} },
    { MODKEY,                XK_space,           setlayout,           {0} },
    { MODKEY|ShiftMask,      XK_space,           togglefloating,      {0} },
	{ MODKEY,                XK_f,               togglefullscr,       {0} },
    { MODKEY,                XK_m,               spawn,               SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; kill -10 $(pidof dwmblocks)") },
    { MODKEY,                XK_minus,           spawn,               SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -2%; kill -10 $(pidof dwmblocks)") },
    { MODKEY,                XK_equal,           spawn,               SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +2%; kill -10 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,      XK_minus,           spawn,               SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%; kill -10 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,      XK_equal,           spawn,               SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%; kill -10 $(pidof dwmblocks)") },
    { MODKEY,                XK_BackSpace,       spawn,               SHCMD("dm-sys") },
    { MODKEY,                XK_grave,           spawn,               SHCMD("dunstctl close") },
    { MODKEY|ShiftMask,      XK_b,               spawn,               SHCMD("dm-bluetooth") },
    { 0,                     XK_Print,           spawn,               SHCMD("dm-maim") },
    // { MODKEY,                XK_w,               spawn,               SHCMD("brave-browser-nightly") },
    // { MODKEY,                XK_e,               spawn,               SHCMD("brave") },
    { MODKEY,                XK_w,               spawn,               {.v = (const char*[]){ "brave-browser-nightly", "--class=B1", NULL } } },
    { MODKEY,                XK_e,               spawn,               {.v = (const char*[]){ "brave", "--class=B2", NULL } } },
    { MODKEY|ShiftMask,      XK_f,               spawn,               SHCMD("ferdium") },
    { MODKEY,                XK_s,               spawn,               SHCMD("librewolf") },
    { MODKEY|ShiftMask,      XK_s,               spawn,               SHCMD("signal-desktop") },
    { MODKEY,                XK_n,               spawn,               SHCMD("obsidian") },
    { MODKEY,                XK_p,               spawn,               {.v = (const char*[]){ "mpc", "toggle", NULL } } },
    { MODKEY,                XK_bracketleft,     spawn,               {.v = (const char*[]){ "mpc", "volume", "-5", NULL } } },
    { MODKEY,                XK_bracketright,    spawn,               {.v = (const char*[]){ "mpc", "volume", "+5", NULL } } },
    { MODKEY|ShiftMask,      XK_bracketleft,     spawn,               {.v = (const char*[]){ "mpc", "prev", NULL } } },
    { MODKEY|ShiftMask,      XK_bracketright,    spawn,               {.v = (const char*[]){ "mpc", "next", NULL } } },
    { MODKEY|ShiftMask,      XK_semicolon,       spawn,               SHCMD("dm-kill") },
    { MODKEY,                XK_apostrophe,      spawn,               SHCMD("dm-mount") },
    { MODKEY|ShiftMask,      XK_apostrophe,      spawn,               SHCMD("dm-umount") },
    { MODKEY,                XK_Delete,          spawn,               SHCMD("dm-kill") },
    { MODKEY,                XK_u,               spawn,               SHCMD("urls") },
    { MODKEY,                XK_i,               spawn,               SHCMD("dm-nm") },
    { MODKEY|ShiftMask,      XK_i,               spawn,               {.v = (const char*[]){ "st", "-e", "sudo", "nmtui", NULL } } },
    { MODKEY,                XK_r,               spawn,               SHCMD("remaps us; kill -10 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,      XK_r,               spawn,               SHCMD("remaps pl; kill -10 $(pidof dwmblocks)") },
    { MODKEY,                XK_0,               spawn,               SHCMD("dm-display") },
    { MODKEY,                XK_c,               spawn,               SHCMD("chromium") },
    { MODKEY|ShiftMask,      XK_c,               spawn,               SHCMD("clear-clipboard") },
    { MODKEY,                XK_period,          viewnext,            {0} },
    { MODKEY,                XK_Tab,             viewnext,            {0} },
    { MODKEY|ShiftMask,      XK_period,          tagtonext,           {0} },
    { MODKEY|ShiftMask,      XK_Tab,             tagtonext,           {0} },
    { MODKEY,                XK_comma,           viewprev,            {0} },
    { MODKEY,                XK_Escape,          viewprev,            {0} },
    { MODKEY|ShiftMask,      XK_comma,           tagtoprev,           {0} },
    { MODKEY|ShiftMask,      XK_Escape,          tagtoprev,           {0} },
	{ MODKEY,                XK_z,               incrgaps,            {.i = +2 } },
	{ MODKEY,                XK_x,               incrgaps,            {.i = -2 } },
	{ MODKEY,                XK_a,               togglegaps,          {0} },
	{ MODKEY|ShiftMask,      XK_a,               defaultgaps,         {0} },
    // { MODKEY,                XK_z,               zoom,                {0} },
    // { MODKEY,                XK_comma,           focusmon,            {.i = -1 } },
    // { MODKEY,                XK_period,          focusmon,            {.i = +1 } },
    // { MODKEY|ShiftMask,      XK_comma,           tagmon,              {.i = -1 } },
    // { MODKEY|ShiftMask,      XK_period,          tagmon,              {.i = +1 } },
    TAGKEYS(                 XK_1,                                    0)
    TAGKEYS(                 XK_2,                                    1)
    TAGKEYS(                 XK_3,                                    2)
    TAGKEYS(                 XK_4,                                    3)
    TAGKEYS(                 XK_5,                                    4)
    TAGKEYS(                 XK_6,                                    5)
    TAGKEYS(                 XK_7,                                    6)
    TAGKEYS(                 XK_8,                                    7)
    TAGKEYS(                 XK_9,                                    8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

