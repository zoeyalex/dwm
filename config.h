/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx      = 3;        /* border pixel of windows */
static const unsigned int gappx         = 20;       /* gaps between windows 45 default*/
static const unsigned int snap          = 32;       /* snap pixel */
static const int showbar                = 1;        /* 0 means no bar */
static const int topbar                 = 1;        /* 0 means bottom bar */
static const int vertpad                = 0;       /* vertical padding of bar */
static const int sidepad                = 10;       /* horizontal padding of bar */

/* fonts */
static const char *fonts[]              = { "Terminus:pixelsize=14:antialias=true:autohint=true:style=Bold" };/*"BmPlusIBMVGA8x16:pixelsize=16:antialias=true:autohint=true:style=Regular" };*/
static const char dmenufont[]           = { "Terminus:pixelsize=14:antialias=true:autohint=true:style=Bold" };/*"BmPlusIBMVGA8x16:pixelsize=16:antialias=true:autohint=true:style=Regular";*/
/* palette */
static const char col_bg[]              = "#000000";
static const char col_fg[]              = "#FFFFFF";

/* opacity */
static const unsigned int baralpha      = 140;
static const unsigned int borderalpha   = 140;

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg,    col_bg,    "black"},
	[SchemeSel]  = { col_bg,    col_fg,    "#555555"},
};
static const unsigned int alphas[][3]      = {
	/*               fg         bg         border     */
	[SchemeNorm] = { OPAQUE,    -1,        borderalpha},
	[SchemeSel]  = { OPAQUE,    -1,        borderalpha },
};
/* tagging */
static const char *tags[] = { "1", "2", "3", "Q", "W", "E"};

static const unsigned int ulinepad	= 5;	    /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	        /* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title       tags mask     isfloating   monitor */
	{ "Signal",       NULL,       NULL,       1 << 1,       0,           -1 },
	{ "qutebrowser",  NULL,       NULL,       1 << 0,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",       tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define FN_F9   0x1008FF12
#define FN_F10  0x1008FF11
#define FN_F11	0x1008FF13
#define MODKEY Mod1Mask
#define LOCKKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] =           { "dmenu_run", "-i", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_fg, "-sf", col_bg, NULL };
static const char *termcmd[]  =           { "st", NULL };
static const char *lockscreen[] =         { "slock", "-m", "Locked", NULL};
static const char *printscreen[] =        { "flameshot", "full", "-c", NULL };
static const char *printscreen_select[] = { "flameshot", "gui", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	//{ 0,                            FN_F9,     spawn,          SHCMD("pactl set-sink-mute 0 toggle; sh ~/.local/bin/status/status.sh")},
	//{ 0,                            FN_F10,    spawn,          SHCMD("pactl set-sink-volume 0 -5%; sh ~/.local/bin/status/status.sh")},
	//{ 0,                            FN_F11,    spawn,          SHCMD("pactl set-sink-volume 0 +5%;sh ~/.local/bin/status/status.sh")},

	{ 0,                            FN_F9,     spawn,          SHCMD("amixer set Master toggle; sh ~/.local/bin/status/status.sh")},
	{ 0,                            FN_F10,    spawn,          SHCMD("amixer set Master 5%-; sh ~/.local/bin/status/status.sh")},
	{ 0,                            FN_F11,    spawn,          SHCMD("amixer set Master 5%+; sh ~/.local/bin/status/status.sh")},
	{ 0,                            XK_Print,  spawn,          {.v = printscreen } },
	{ ShiftMask,                    XK_Print,  spawn,          {.v = printscreen_select } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		    XK_Return, spawn,          {.v = termcmd } },
	{ LOCKKEY,                      XK_l,      spawn,          {.v = lockscreen } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	/*
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	*/
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_m, 	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_Return, setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	/*
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	*/
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_q,                      3)
	TAGKEYS(                        XK_w,                      4)
	TAGKEYS(                        XK_e,                      5)
	{ MODKEY|ShiftMask,             XK_l,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
