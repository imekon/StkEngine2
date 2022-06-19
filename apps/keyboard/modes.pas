unit modes;

{$mode ObjFPC}{$H+}

interface

uses
  Classes, SysUtils, mode;

type

  { TModes }

  TModes = class
  private
    m_modes: TModeMap;
  public
    constructor Create;
    destructor Destroy; override;
    function FindMode(const name: string): TMode;
    function GetModes: TStringList;
  end;

implementation

const
  modeCount = 34;

  modeNames: array [0..modeCount - 1] of string =
    (
        'Major',
        'Minor',
        'Harmonic',
        'Melodic',
        'Dorian',
        'Phrygian',
        'Lydian',
        'Mixolydian',
        'Locrian',
        'Major Blues',
        'Minor Blues',
        'Diminished',
        'Combination Diminished',
        'Major Pentatonic',
        'Minor Pentatonic',
        'Raga Bhairav',
        'Raga Gamanasrama',
        'Raga Todi',
        'Arabian',
        'Spanish',
        'Gypsy',
        'Egyptian',
        'Hawaiian',
        'Bali Island Pelog',
        'Japanese Miyakobushi',
        'Ryukyu',
        'Chinese',
        'Bass Line',
        'Whole Tone',
        'Minor 3rd Interval',
        'Major 3rd Interval',
        '4th Interval',
        '5th Interval',
        'Octave'
    );

  // C  C#  D  D#  E  F  F#  G  G#  A  A#  B
  // 0   1  2   3  4  5   6  7   8  9  10  11

  keyMapping: array [0..modeCount - 1, 0..7] of integer =
    (
        ( 0, 2, 4, 5, 7, 9, 11,     -1 ),         // Major or Ionian
        ( 0, 2, 3, 5, 7, 8, 10,     -1 ),         // Natural Minor or Aeolian
        ( 0, 2, 3, 5, 7, 8, 11,     -1 ),         // Harmonic minor
        ( 0, 2, 3, 5, 7, 9, 11,     -1 ),         // Melodic Minor
        ( 0, 2, 3, 5, 7, 9, 10,     -1 ),         // Dorian
        ( 0, 1, 3, 5, 7, 8, 10,     -1 ),         // Phrygian
        ( 0, 2, 4, 6, 7, 9, 11,     -1 ),         // Lydian
        ( 0, 2, 4, 5, 7, 9, 10,     -1 ),         // Mixolydian
        ( 0, 1, 3, 5, 6, 8, 10,     -1 ),         // Locrian

        ( 0, 2, 3, 4, 5, 7,         -1, -1 ),     // Major Blues
        ( 0, 3, 5, 6, 7, 10,        -1, -1 ),     // Minor Blues
        ( 0, 2, 3, 6, 8, 9, 11,     -1 ),         // Diminished
        ( 0, 1, 3, 4, 6, 7, 9, 10 ),              // Combination Diminished
        ( 0, 2, 4, 7, 9,            -1, -1, -1 ), // Major Pentatonic
        ( 0, 3, 5, 7, 10,           -1, -1, -1 ), // Minor Pentatonic
        ( 0, 1, 4, 5, 7, 8, 11,     -1 ),         // Raga Bhairav
        ( 0, 1, 4, 6, 7, 8, 11,     -1 ),         // Raga Gamanasrama
        ( 0, 1, 3, 6, 7, 8, 11,     -1 ),         // Raga Todi
        ( 0, 2, 4, 5, 6, 8, 10,     -1 ),         // Arabian
        ( 0, 1, 3, 4, 6, 7, 8, 11 ),              // Spanish
        ( 0, 2, 3, 6, 7, 8, 11,     -1 ),         // Gypsy
        ( 0, 2, 5, 7, 10,           -1, -1, -1 ), // Egyptian
        ( 0, 2, 3, 7, 9,            -1, -1, -1 ), // Hawaiian
        ( 0, 1, 3, 7, 8,            -1, -1, -1 ), // Bali Island Pelog
        ( 0, 1, 5, 7, 8,            -1, -1, -1 ), // Japanese Miyakobushi
        ( 0, 4, 5, 7, 11,           -1, -1, -1 ), // Ryukyu
        ( 0, 4, 6, 7, 11,           -1, -1, -1 ), // Chinese
        ( 0, 7, 10,                 -1, -1, -1, -1, -1 ), // Bass line
        ( 0, 2, 4, 6, 8, 10,        -1, -1 ),     // Whole tone
        ( 0, 3, 6, 9,               -1, -1, -1, -1 ),   // Minor 3rd interval
        ( 0, 4, 8,                  -1, -1, -1, -1, -1 ),  // Major 3rd interval
        ( 0, 5, 10,                 -1, -1, -1, -1, -1 ), // 4th interval
        ( 0, 7,                     -1, -1, -1, -1, -1, -1 ), // 5th interval
        ( 0,                        -1, -1, -1, -1, -1, -1, -1 ) // Octave
    );

{ TModes }

constructor TModes.Create;
var
  i: integer;
  mode: TMode;

begin
  m_modes := TModeMap.Create;

  for i := Low(modeNames) to High(modeNames) do
  begin
    mode := TMode.Create(modeNames[i], keyMapping[i]);
    m_modes.Add(modeNames[i], mode);
  end;
end;

destructor TModes.Destroy;
begin
  m_modes.Free;
  inherited Destroy;
end;

function TModes.FindMode(const name: string): TMode;
begin
  result := m_modes[name];
end;

function TModes.GetModes: TStringList;
var
  i: integer;
  list: TStringList;

begin
  list := TStringList.Create;
  for i := 0 to m_modes.Count - 1 do
  begin
    list.Add(m_modes.Keys[i]);
  end;
  result := list;
end;

end.

