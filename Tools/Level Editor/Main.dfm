object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'DwarfStar Level Editor'
  ClientHeight = 400
  ClientWidth = 440
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object paView: TPanel
    Left = 40
    Top = 0
    Width = 400
    Height = 400
    Align = alClient
    BevelOuter = bvNone
    Ctl3D = False
    DoubleBuffered = True
    ParentBackground = False
    ParentCtl3D = False
    ParentDoubleBuffered = False
    ShowCaption = False
    TabOrder = 0
    OnResize = paViewResize
  end
  object paToolbar: TPanel
    Left = 0
    Top = 0
    Width = 40
    Height = 400
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    object btFiles: TBitBtn
      AlignWithMargins = True
      Left = 2
      Top = 2
      Width = 36
      Height = 36
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alTop
      TabOrder = 0
    end
  end
end
