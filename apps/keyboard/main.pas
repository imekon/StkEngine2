unit main;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ExtCtrls,
  StkEngine2, modes;

type

  { TMainForm }

  TMainForm = class(TForm)
    ModeList: TComboBox;
    Label2: TLabel;
    KeyBox: TPaintBox;
    ScaleList: TComboBox;
    Label1: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure OnKeyBoxDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure OnKeyBoxUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure OnKeyPaint(Sender: TObject);
  private
    m_osc: TParametricOsc;
    m_modes: TModes;
  public
  end;

var
  MainForm: TMainForm;

implementation

{$R *.lfm}

{ TMainForm }

const
  KeyWidth = 18;
  NoteBase = 12 * 3;

procedure TMainForm.FormCreate(Sender: TObject);
var
  i: integer;
  modes: TStringList;

begin
  Initialise;
  Start;

  m_osc := CreateMonoSynth;
  m_modes := TModes.Create;

  ScaleList.ItemIndex := 0;

  modes := m_modes.GetModes;

  for i := 0 to modes.Count - 1 do
  begin
    ModeList.Items.Add(modes[i]);
  end;

  ModeList.ItemIndex := 0;
end;

procedure TMainForm.FormDestroy(Sender: TObject);
begin
  Stop;
  DestroySynth(m_osc);
  Shutdown;
  FreeAndNil(m_modes);
end;

procedure TMainForm.OnKeyBoxDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  NoteOn(m_osc, x div KeyWidth + NoteBase, 0.7);
end;

procedure TMainForm.OnKeyBoxUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  NoteOff(m_osc, x div KeyWidth + NoteBase, 0.3);
end;

procedure TMainForm.OnKeyPaint(Sender: TObject);
var
  i, n: integer;

begin
  with KeyBox.Canvas do
  begin
    Brush.Color := clWhite;
    n := KeyBox.Width div KeyWidth + 1;
    for i := 0 to n do
      Rectangle(i * KeyWidth, 0, i * KeyWidth + KeyWidth, KeyBox.Height);
  end;
end;

end.

