object GeometricVectorFrame: TGeometricVectorFrame
  Left = 0
  Top = 0
  Width = 308
  Height = 21
  DoubleBuffered = True
  Color = clWhite
  ParentBackground = False
  ParentColor = False
  ParentDoubleBuffered = False
  TabOrder = 0
  object paMain: TPanel
    Left = 0
    Top = 0
    Width = 308
    Height = 21
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 233
    object laX: TLabel
      AlignWithMargins = True
      Left = 0
      Top = 0
      Width = 6
      Height = 13
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 5
      Margins.Bottom = 0
      Align = alRight
      Caption = 'X'
      Layout = tlCenter
    end
    object laY: TLabel
      AlignWithMargins = True
      Left = 111
      Top = 0
      Width = 6
      Height = 13
      Margins.Left = 25
      Margins.Top = 0
      Margins.Right = 5
      Margins.Bottom = 0
      Align = alRight
      Caption = 'Y'
      Layout = tlCenter
    end
    object laZ: TLabel
      AlignWithMargins = True
      Left = 222
      Top = 0
      Width = 6
      Height = 13
      Margins.Left = 25
      Margins.Top = 0
      Margins.Right = 5
      Margins.Bottom = 0
      Align = alRight
      Caption = 'Z'
      Layout = tlCenter
    end
    object edX: TEdit
      Left = 11
      Top = 0
      Width = 75
      Height = 21
      Align = alRight
      TabOrder = 0
      Text = '0'
      OnChange = edXChange
      ExplicitLeft = -39
    end
    object edY: TEdit
      Left = 122
      Top = 0
      Width = 75
      Height = 21
      Align = alRight
      TabOrder = 1
      Text = '0'
      OnChange = edYChange
      ExplicitLeft = 72
    end
    object edZ: TEdit
      Left = 233
      Top = 0
      Width = 75
      Height = 21
      Align = alRight
      TabOrder = 2
      Text = '0'
      OnChange = edZChange
      ExplicitLeft = 183
    end
  end
end