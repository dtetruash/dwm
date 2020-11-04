/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 3;        /* border pixel of windows */
static const unsigned int snap = 32;       /* snap pixel */
static const unsigned int gappih = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv = 10;       /* vert inner gap between windows */
static const unsigned int gappoh = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar = 1;        /* 0 means no bar */
static const int topbar = 1;        /* 0 means bottom bar */
static const char* fonts[] = { "monospace:size=10" };
static const char dmenufont[] = "monospace:size=10";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";

static const char col_gruvbox_bg0[] = "#282828";
static const char col_gruvbox_bg1[] = "#3c3836";
static const char col_gruvbox_bg2[] = "#504945";
static const char col_gruvbox_bg3[] = "#665c54";
static const char col_gruvbox_bg4[] = "#7c6f64";
static const char col_gruvbox_fg[] = "#ebdbb2";
static const char col_gruvbox_orange[] = "#d65d0e";
static const char col_gruvbox_red[] = "#cc241d";
static const char col_gruvbox_green[] = "#98971a";
static const char col_gruvbox_yellow[] = "#d79921";
static const char col_gruvbox_blue[] = "#458588";
static const char col_gruvbox_purple[] = "#b16286";
static const char col_gruvbox_aqua[] = "#689d6a";
static const char col_gruvbox_gray[] = "#a89984";

static const char col_wallpaper_bg[] = "#20241d";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gruvbox_bg3, col_gruvbox_bg0,  col_gruvbox_aqua },
	[SchemeSel] = { col_gruvbox_bg4, col_gruvbox_bg0,  col_gruvbox_orange },

	[SchemeStatus] = { col_gruvbox_bg3, col_gruvbox_bg0,  "#000000" },   // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel] = { col_gruvbox_red, col_gruvbox_bg1,  "#000000" },   // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm] = { col_gruvbox_bg4, col_gruvbox_bg0,  "#000000" },   // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel] = { col_gruvbox_fg, col_wallpaper_bg, "#000000" },   // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm] = { col_gruvbox_fg, col_wallpaper_bg,  "#000000" },   // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char* dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gruvbox_bg0, "-nf", col_gruvbox_bg4, "-sb", col_gruvbox_red, "-sf", col_gruvbox_fg, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

