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

procedure TMainForm.OnKeyPaint(Sender: TObject);
begin
  with KeyBox.Canvas do
  begin
    Rectangle(10, 10, 20, 40);
  end;
end;

end.

