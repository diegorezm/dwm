/* See LICENSE file for copyright and license details. */

#define TERMINAL_ENV
#define BROWSER_ENV

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int gappx = 4;    /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"JetBrainsMono Nerd Font:size=10"};
static const char dmenufont[] = "JetBrainsMono:size=11";
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;

const char *spcmd1[] = {
    "alacritty",
    "--class",
    "spterm,spterm",
    "--option",
    "window.dimensions.columns=120",
    "--option",
    "window.dimensions.lines=34",
    "--option",
    "font.size=13",
    NULL
};

const char *spcmd2[] = {"thunar", NULL};
const char *spcmd3[] = {"pavucontrol", NULL};
const char *spcmd4[] = {"spotify-launcher", NULL};

static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm", spcmd1},
    {"thunar", spcmd2},
    {"pavucontrol", spcmd3},
    {"spotify", spcmd4},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"discord", NULL, NULL, 1 << 8, 0, 1},
    {"steam", NULL, NULL, 1 << 7, 0, 1},
    {"Sxiv", NULL, NULL, 0, 1, -1},
    {NULL, "spterm", NULL, SPTAG(0), 1, -1},
    {NULL, "thunar", NULL, SPTAG(1), 1, -1},
    {NULL, "pavucontrol", NULL, SPTAG(2), 1, -1},
    {NULL, "spotify", NULL, SPTAG(3), 1, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */
static const int refreshrate =
    120; /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run",    "-fn", dmenufont,   "-nb",
                                 normbgcolor,    "-nf", normfgcolor, "-sb",
                                 selbordercolor, "-sf", selfgcolor,  NULL};

static const char *nextsongcmd[] = {"playerctl", "-p", "spotify", "next", NULL};
static const char *toggleplayingcmd[] = {"playerctl", "-p", "spotify",
                                         "play-pause", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */

    // SPAWNS
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_w, spawn, {.v = browsercmd}},

    // SHELL COMMANDS
    {MODKEY, XK_F1, spawn, SHCMD("$HOME/.local/bin/scripts/power_ctl")},
    {0x0, XK_Print, spawn, SHCMD("$HOME/.local/bin/scripts/screenshot")},
    {MODKEY, XK_z, spawn, SHCMD("$HOME/.local/bin/scripts/dir_quick_search")},
    {MODKEY, XK_c, spawn,
     SHCMD("$HOME/.local/bin/scripts/config_quick_search")},

    // SONG
    {MODKEY, XK_n, spawn, {.v = nextsongcmd}},
    {MODKEY, XK_p, spawn, {.v = toggleplayingcmd}},

    // TOGGLE TOP BAR
    {MODKEY, XK_b, togglebar, {0}},

    // WINDOW UTILS
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},

    {MODKEY | ShiftMask, XK_f, togglefullscr, {0}},
    {MODKEY | ShiftMask, XK_i, incnmaster, {.i = +1}},
    {MODKEY | ShiftMask, XK_d, incnmaster, {.i = -1}},

    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},

    // LAYOUTS
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    // {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},

    // WORKSPACE UTILS
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},

    // SCRATCHPADS
    {MODKEY, XK_s, togglescratch, {.ui = 0}},
    {MODKEY, XK_e, togglescratch, {.ui = 1}},
    {MODKEY, XK_a, togglescratch, {.ui = 2}},
    {MODKEY, XK_m, togglescratch, {.ui = 3}},

    // RELOAD XRDB
    {MODKEY, XK_F5, xrdb, {.v = NULL}},

    // VOLUME KEYS
    {MODKEY, XK_F10, spawn,
     SHCMD("pamixer -d 10 && pkill -RTMIN+10 dwmblocks")},
    {MODKEY, XK_F11, spawn,
     SHCMD("pamixer -i 10 && pkill -RTMIN+10 dwmblocks")},

    // GAPS
    {MODKEY, XK_minus, setgaps, {.i = -1}},
    {MODKEY, XK_equal, setgaps, {.i = +1}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button1, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
