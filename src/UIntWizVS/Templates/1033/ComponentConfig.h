///////////////////////////////////////////////////////////////////////////
// ComponentConfig.h, component configuration parameters.
//
// Initially generated by the component wizard. Feel free to manually edit.
///////////////////////////////////////////////////////////////////////////

// Component framework type
[!if COMPONENT_FRAMEWORK == "RAW"]
#define RAWCOMPONENT
[!endif]
[!if COMPONENT_FRAMEWORK == "BON"]
#define BONCOMPONENT
[!endif]
[!if COMPONENT_FRAMEWORK == "BON2"]
#define BON2COMPONENT
[!endif]

// COM UUID-s, names and progID
#define TYPELIB_UUID "[!output TYPELIB_UUID]"
#define TYPELIB_NAME "[!output TYPELIB_NAME]"
#define COCLASS_UUID "[!output COCLASS_UUID]"
#define COCLASS_NAME "[!output COCLASS_NAME]"
#define COCLASS_PROGID "[!output COCLASS_PROGID]"

#define COCLASS_UUID_EXPLODED1  [!output COCLASS_UUID_EXPLODED1]
#define COCLASS_UUID_EXPLODED2  [!output COCLASS_UUID_EXPLODED2]
#define COCLASS_UUID_EXPLODED3  [!output COCLASS_UUID_EXPLODED3]
#define COCLASS_UUID_EXPLODED4  [!output COCLASS_UUID_EXPLODED4]
#define COCLASS_UUID_EXPLODED5  [!output COCLASS_UUID_EXPLODED5]
#define COCLASS_UUID_EXPLODED6  [!output COCLASS_UUID_EXPLODED6]
#define COCLASS_UUID_EXPLODED7  [!output COCLASS_UUID_EXPLODED7]
#define COCLASS_UUID_EXPLODED8  [!output COCLASS_UUID_EXPLODED8]
#define COCLASS_UUID_EXPLODED9  [!output COCLASS_UUID_EXPLODED9]
#define COCLASS_UUID_EXPLODED10 [!output COCLASS_UUID_EXPLODED10]
#define COCLASS_UUID_EXPLODED11 [!output COCLASS_UUID_EXPLODED11]


// This name will appear in the popup window for interpreter selection.
#define COMPONENT_NAME "[!output COMPONENT_NAME]"


// This text will appear in the toolbar icon tooltip and in the menu.
#define TOOLTIP_TEXT "[!output TOOLTIP_TEXT]"

// This macro determines the component type (addon vs. interpreter):
[!if GME_INTERPRETER]
#define GME_INTERPRETER
[!endif]
[!if GME_ADDON]
#define GME_ADDON
#define ADDON_EVENTMASK [!output ADDON_EVENTMASK]
[!endif]

// The name of the paradigm(s). The GME will use this component
// for this paradigm. Separate the names of paradigms by commas.
[!if PARADIGM_INDEPENDENT]
#define PARADIGM_INDEPENDENT
[!else]
#define PARADIGMS "[!output PARADIGMS]"
[!endif]


[!if BON_ICON_SUPPORT]
#define BON_ICON_SUPPORT
[!else]
// not defined: #define BON_ICON_SUPPORT
[!endif]

[!if REGISTER_SYSTEMWIDE]
#define REGISTER_SYSTEMWIDE
[!else]
// not defined: #define REGISTER_SYSTEMWIDE
[!endif]

#define GME_COMPONENT_ISUPPORTERRORINFO
