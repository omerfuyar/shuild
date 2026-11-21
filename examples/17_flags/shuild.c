#include "../../../shu/shu.h"
#include "../../shuild.h"

/*
    This example shows how a build script reads its flags:
    it lists them once, and shuild reads them and prints their help.
    Try: ./shuild -h, ./shuild -b release -e, ./shuild -t one two, ./shuild -x
*/

typedef enum BuildType
{
    BuildType_Debug,
    BuildType_Release,
} BuildType;

static const SHUFlagChoice BUILD_TYPES[] = {
    {"debug", "the default, with debug information"},
    {"release", "an optimized build"},
    {NULL, NULL},
};

static int type = BuildType_Debug;
static const char *compiler = NULL;
static bool extras = false;
static SHUFlagList tests = {0};
static bool help = false;

static const SHUFlag FLAGS[] = {
    SHU_FLAG_CHOICE("-b", "--build", "TYPE", &type, BUILD_TYPES, "Build type:"),
    SHU_FLAG_STRING("-c", "--compiler", "CC", &compiler, "The compiler, or the newest on PATH"),
    SHU_FLAG_SWITCH("-e", "--extras", &extras, "Also build the extras"),
    SHU_FLAG_LIST("-t", "--test", "NAME", &tests, "Run the tests named,\nor every test"),
    SHU_FLAG_SWITCH("-h", "--help", &help, "Show this help"),
};

int main(int argc, char **argv)
{
    // the flags are read before the compiler is configured, as they may choose it
    SHU_FlagsRead(FLAGS, argc, argv);
    SHU_CompilerConfigureTry(compiler);

    // a changed script is compiled again and run with the same arguments, so the new program reports a bad one
    SHU_UtilAutomate(argc, argv);

    if (help)
    {
        SHU_FlagsPrintHelp(FLAGS);
        return 0;
    }

    SHU_FlagsCheck(FLAGS);

    SHU_UtilLog("build type " SHUM_LOG_VALUE("%s") ", extras %s, %d tests named", BUILD_TYPES[type].name, extras ? "on" : "off", tests.count);

    SHU_Module("example", NULL, SHUModuleType_Executable, NULL)
    {
        SHU_ModuleAddSourceFiles("example.c");
    }

    return 0;
}
