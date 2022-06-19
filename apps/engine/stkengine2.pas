unit StkEngine2;

{$mode ObjFPC}{$H+}

interface

uses
  windows;

const
  STK_DLL = 'stkengine2.dll';

const
  STK_OSC_TYPE_NONE = 0;
  STK_OSC_TYPE_SAW = 1;
  STK_OSC_TYPE_SQUARE = 2;
  STK_OSC_TYPE_SINE = 3;
  STK_OSC_TYPE_NOISE = 4;

  STK_GLOBAL_STATUS = 0;
  STK_GLOBAL_REVERB_MIX = 1;
  STK_GLOBAL_REVERB_ROOMSIZE = 2;
  STK_GLOBAL_REVERB_DAMPING = 3;
  STK_GLOBAL_REVERB_WIDTH = 4;
  STK_GLOBAL_REVERB_MODE = 5;
  STK_GLOBAL_VULEFT = 6;
  STK_GLOBAL_VURIGHT = 7;
  STK_GLOBAL_VOLUME = 8;

  STK_GLOBAL_MAX = 9;

  STK_PARAMETER_OSC1_TYPE = 0;
  STK_PARAMETER_OSC1_GAIN = 1;
  STK_PARAMETER_OSC1_COARSE = 2;
  STK_PARAMETER_OSC1_FINE = 3;

  STK_PARAMETER_OSC2_TYPE = 4;
  STK_PARAMETER_OSC2_GAIN = 5;
  STK_PARAMETER_OSC2_COARSE = 6;
  STK_PARAMETER_OSC2_FINE = 7;

  STK_PARAMETER_OSC3_TYPE = 8;
  STK_PARAMETER_OSC3_GAIN = 9;
  STK_PARAMETER_OSC3_COARSE = 10;
  STK_PARAMETER_OSC3_FINE = 11;

  STK_FILTER_TYPE = 12;
  STK_FILTER_CUTOFF = 13;
  STK_FILTER_RES = 14;

  STK_ENVELOPE_ATTACK = 15;
  STK_ENVELOPE_DECAY = 16;
  STK_ENVELOPE_SUSTAIN = 17;
  STK_ENVELOPE_RELEASE = 18;

  STK_FILTER_ENVELOPE_ATTACK = 19;
  STK_FILTER_ENVELOPE_DECAY = 20;
  STK_FILTER_ENVELOPE_SUSTAIN = 21;
  STK_FILTER_ENVELOPE_RELEASE = 22;
  STK_FILTER_ENVELOPE_MIX = 23;

  STK_PARAMETER_LEFT = 24;
  STK_PARAMETER_RIGHT = 25;

  STK_PARAMETER_PANNING = 26;
  STK_REVERB_MIX = 27;

  STK_PARAMETER_MAX = 28;

  STK_EFFECT_BYPASS = 0;

  STK_EFFECT_MIX = 1;
  STK_EFFECT_DELAY = 2;
  STK_EFFECT_FEEDBACK = 3;
  STK_EFFECT_PINGPONG = 4;

  STK_EFFECT_MOD_DEPTH = 1;
  STK_EFFECT_MOD_FREQ = 2;

  STK_EFFECT_MAX = 5;

  STK_VERSION_DUKTAPE = 0;
  STK_VERSION_SYNTHESIS = 1;
  STK_VERSION_ENGINE = 2;

type
  TSynthReturn = record
    errorCode: integer;
    errorMessage: array [0..255] of AnsiChar;
  end;

  TParametricOsc = Pointer;
  TEffect = Pointer;
  TMIDIInputPtr = Pointer;
  TMIDIOutputPtr = Pointer;

  function StkScriptInitialise: TSynthReturn; stdcall;
  function StkScriptShutdown: TSynthReturn; stdcall;
  function StkScriptReadFile(filename: PAnsiChar): TSynthReturn; stdcall;
  function StkScriptEvaluate(text: PAnsiChar): TSynthReturn; stdcall;

  procedure Initialise; stdcall;
  procedure Shutdown; stdcall;
  procedure Start; stdcall;
  procedure Stop; stdcall;

  function GetEngineVersion(version: integer): PAnsiChar; stdcall;

  function GetMessageCount: integer; stdcall;
  function GetMessageText: PAnsiChar; stdcall;
  function WaitText: BOOL; stdcall;

  function GetGlobalParam(global: integer): double; stdcall;
  procedure SetGlobalParam(global: integer; value: double); stdcall;

  function GetControlFlag(index: integer): BOOL; stdcall;
  procedure SetControlFlag(index: integer; flag: BOOL); stdcall;
  function GetControlValue(index: integer): double; stdcall;
  procedure SetControlValue(index: integer; value: double); stdcall;

  procedure SetTempo(tempo: double; steps: integer); stdcall;
  function WaitTick: BOOL; stdcall;

  function CreateMonoSynth: TParametricOsc; stdcall;
  function CreatePolySynth(voiceCount: integer): TParametricOsc; stdcall;
  function CreateSamplerSynth: TParametricOsc; stdcall;
  function CreateMoogSynth: TParametricOsc; stdcall;
  procedure DestroySynth(osc: TParametricOsc); stdcall;

  function CreateEchoEffect: TEffect; stdcall;
  function CreateChorusEffect: TEffect; stdcall;
  procedure DestroyEffect(effect: TEffect); stdcall;

  procedure OscAddEffect(osc: TParametricOsc; effect: TEffect); stdcall;
  procedure OscRemoveEffect(osc: TParametricOsc; effect: TEffect); stdcall;

  procedure SetOscParam(osc: TParametricOsc; parameter: integer; value: double); stdcall;
  function GetOscParam(osc: TParametricOsc; parameter: integer): double; stdcall;

  procedure LoadParams(osc: TParametricOsc; parameters: array of double); stdcall;
  procedure SaveParams(osc: TParametricOsc; parameters: array of double); stdcall;

  procedure SetEffectParam(effect: TEffect; parameter: integer; value: double); stdcall;
  function GetEffectParam(effect: TEffect; parameter: integer): double; stdcall;

  procedure NoteOn(osc: TParametricOsc; note: integer; amplitude: double); stdcall;
  procedure NoteOff(osc: TParametricOsc; note: integer; amplitude: double); stdcall;

  function MIDIGetInputDeviceCount: integer; stdcall;
  function MIDIGetOutputDeviceCount: integer;  stdcall;

  procedure MIDIGetInputDeviceName(device: integer; name: PAnsiChar; size: integer); stdcall;
  procedure MIDIGetOutputDeviceName(device: integer; name: PAnsiChar; size: integer); stdcall;

  function MIDICreateInput(device: integer): TMIDIInputPtr; stdcall;
  function MIDIGetInput(device: TMIDIInputPtr; index: integer): integer; stdcall;
  procedure MIDICloseInput(device: TMIDIInputPtr); stdcall;

implementation

function StkScriptInitialise: TSynthReturn; stdcall; external STK_DLL;
function StkScriptShutdown: TSynthReturn; stdcall; external STK_DLL;
function StkScriptReadFile(filename: PAnsiChar): TSynthReturn; stdcall; external STK_DLL;
function StkScriptEvaluate(text: PAnsiChar): TSynthReturn; stdcall; external STK_DLL;

procedure Initialise; stdcall; external STK_DLL;
procedure Shutdown; stdcall; external STK_DLL;
procedure Start; stdcall; external STK_DLL;
procedure Stop; stdcall; external STK_DLL;

function GetEngineVersion(version: integer): PAnsiChar; stdcall; external STK_DLL;

function GetMessageCount: integer; stdcall; external STK_DLL;
function GetMessageText: PAnsiChar; stdcall; external STK_DLL;
function WaitText: BOOL; stdcall; external STK_DLL;

function GetGlobalParam(global: integer): double; stdcall; external STK_DLL;
procedure SetGlobalParam(global: integer; value: double); stdcall; external STK_DLL;

function GetControlFlag(index: integer): BOOL; stdcall; external STK_DLL;
procedure SetControlFlag(index: integer; flag: BOOL); stdcall; external STK_DLL;
function GetControlValue(index: integer): double; stdcall; external STK_DLL;
procedure SetControlValue(index: integer; value: double); stdcall; external STK_DLL;

procedure SetTempo(tempo: double; steps: integer); stdcall; external STK_DLL;
function WaitTick: BOOL; stdcall; external STK_DLL;

function CreateMonoSynth: TParametricOsc; stdcall; external STK_DLL;
function CreatePolySynth(voiceCount: integer): TParametricOsc; stdcall; external STK_DLL;
function CreateSamplerSynth: TParametricOsc; stdcall; external STK_DLL;
function CreateMoogSynth: TParametricOsc; stdcall; external STK_DLL;
procedure DestroySynth(osc: TParametricOsc); stdcall; external STK_DLL;

function CreateEchoEffect: TEffect; stdcall; external STK_DLL;
function CreateChorusEffect: TEffect; stdcall; external STK_DLL;
procedure DestroyEffect(effect: TEffect); stdcall; external STK_DLL;

procedure OscAddEffect(osc: TParametricOsc; effect: TEffect); stdcall; external STK_DLL;
procedure OscRemoveEffect(osc: TParametricOsc; effect: TEffect); stdcall; external STK_DLL;

procedure SetOscParam(osc: TParametricOsc; parameter: integer; value: double); stdcall; external STK_DLL;
function GetOscParam(osc: TParametricOsc; parameter: integer): double; stdcall; external STK_DLL;

procedure LoadParams(osc: TParametricOsc; parameters: array of double); stdcall; external STK_DLL;
procedure SaveParams(osc: TParametricOsc; parameters: array of double); stdcall; external STK_DLL;

procedure SetEffectParam(effect: TEffect; parameter: integer; value: double); stdcall; external STK_DLL;
function GetEffectParam(effect: TEffect; parameter: integer): double; stdcall; external STK_DLL;

procedure NoteOn(osc: TParametricOsc; note: integer; amplitude: double); stdcall; external STK_DLL;
procedure NoteOff(osc: TParametricOsc; note: integer; amplitude: double); stdcall; external STK_DLL;

function MIDIGetInputDeviceCount: integer; stdcall; external STK_DLL;
function MIDIGetOutputDeviceCount: integer;  stdcall; external STK_DLL;

procedure MIDIGetInputDeviceName(device: integer; name: PAnsiChar; size: integer); stdcall; external STK_DLL;
procedure MIDIGetOutputDeviceName(device: integer; name: PAnsiChar; size: integer); stdcall; external STK_DLL;

function MIDICreateInput(device: integer): TMIDIInputPtr; stdcall; external STK_DLL;
function MIDIGetInput(device: TMIDIInputPtr; index: integer): integer; stdcall; external STK_DLL;
procedure MIDICloseInput(device: TMIDIInputPtr); stdcall; external STK_DLL;

end.

