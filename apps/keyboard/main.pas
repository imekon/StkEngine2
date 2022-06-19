unit main;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs,
  StkEngine2;

type

  { TMainForm }

  TMainForm = class(TForm)
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    m_osc: TParametricOsc;
  public
  end;

var
  MainForm: TMainForm;

implementation

{$R *.lfm}

{ TMainForm }

procedure TMainForm.FormCreate(Sender: TObject);
begin
  Initialise;
  Start;

  m_osc := CreateMonoSynth;
end;

procedure TMainForm.FormDestroy(Sender: TObject);
begin
  Stop;
  DestroySynth(m_osc);
  Shutdown;
end;

end.

