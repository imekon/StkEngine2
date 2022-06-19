unit mode;

{$mode ObjFPC}{$H+}

interface

uses
  FGL;

type
  TMode = class
  private
    m_name: string;
    m_notes: array of integer;
    m_noteCount: integer;
  public
    constructor Create(const name: string; notes: array of integer);
    function Map(note, scale, chord: integer): integer;
    function IsMapped(note: integer): boolean;
    property Name: string read m_name;
    property NoteCount: integer read m_noteCount;
  end;

  TModeMap = specialize TFPGMapObject<string, TMode>;

implementation

constructor TMode.Create(const name: string; notes: array of integer);
var
  i, index: integer;

begin
  m_name := name;
  m_noteCount := 0;
  SetLength(m_notes, Length(notes));
  index := 0;
  for i := Low(notes) to High(notes) do
  begin
    m_notes[index] := notes[i];
    if notes[i] <> -1 then inc(m_noteCount);
    inc(index);
  end;
end;

function TMode.IsMapped(note: integer): boolean;
var
  i: integer;

begin
  result := false;
  for i := 0 to 11 do
    if m_notes[i] = note then
    begin
      result := true;
      break;
    end;
end;

function TMode.Map(note, scale, chord: integer): integer;
var
  index, octave: integer;

begin
  index := (note + chord) mod m_noteCount;
  octave := (note + chord) div m_noteCount;
  if m_notes[index] <> -1 then
    result := m_notes[index] + scale + octave * 12
  else
    result := -1;
end;

end.

