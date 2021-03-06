#include "Video/Object.h"
#include "Video/Pal.h"
#include "Video/BgMap.h"
#include "Main/DemoReplayInput.h"
#include "Sound/Sound.h"
#include "PlatformTypes.h"

ROMDATA ObjectDataTable Objects;

ROMDATA PalData Pal;

ROMDATA BgMap16 BgMapSection0;
ROMDATA BgMap16 BgMapSection1;
ROMDATA BgMap32 BgMapSection2;
ROMDATA BgMap16 BgMapSection3;
ROMDATA BgMap32 BgMapSection4;
ROMDATA BgMap16 BgMapSection5;
ROMDATA BgMap16 BgMapSection6;
ROMDATA BgMap16 BgMapSection7;
ROMDATA BgMap16 BgMapSection8;
ROMDATA BgMap16 BgMapSection9;
ROMDATA BgMap16 BgMapVersus;

ROMDATA ButtonInput DemoReplayInputTwin[DEMOREPLAY_LENGTH * NUMPLAYERS];
ROMDATA ButtonInput DemoReplayInputDoubles[DEMOREPLAY_LENGTH * NUMPLAYERS];
ROMDATA ButtonInput DemoReplayInputVersus[DEMOREPLAY_LENGTH * NUMPLAYERS];

ROMDATA MidiData Midi;
