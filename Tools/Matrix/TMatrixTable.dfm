inherited MatrixTable: TMatrixTable
  Width = 461
  Height = 193
  DoubleBuffered = True
  ParentDoubleBuffered = False
  ExplicitWidth = 461
  ExplicitHeight = 193
  object paBackground: TPanel
    Left = 0
    Top = 0
    Width = 461
    Height = 193
    Align = alClient
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    object gpMatrix: TGridPanel
      AlignWithMargins = True
      Left = 1
      Top = 1
      Width = 457
      Height = 189
      Margins.Left = 1
      Margins.Top = 1
      Margins.Right = 1
      Margins.Bottom = 1
      Align = alClient
      BevelOuter = bvNone
      ColumnCollection = <
        item
          Value = 19.997678334902590000
        end
        item
          Value = 19.998530515144320000
        end
        item
          Value = 19.999997042503560000
        end
        item
          Value = 20.004651814841450000
        end
        item
          Value = 19.999142292608080000
        end>
      ControlCollection = <
        item
          Column = 1
          Control = laColumn1
          Row = 0
        end
        item
          Column = 2
          Control = laColumn2
          Row = 0
        end
        item
          Column = 3
          Control = laColumn3
          Row = 0
        end
        item
          Column = 0
          Control = laHeader
          Row = 0
        end
        item
          Column = 4
          Control = laColumn4
          Row = 0
        end
        item
          Column = 0
          Control = laLine1
          Row = 1
        end
        item
          Column = 1
          Control = edValue11
          Row = 1
        end
        item
          Column = 2
          Control = edValue12
          Row = 1
        end
        item
          Column = 3
          Control = edValue13
          Row = 1
        end
        item
          Column = 4
          Control = edValue14
          Row = 1
        end
        item
          Column = 0
          Control = laLine2
          Row = 2
        end
        item
          Column = 1
          Control = edValue21
          Row = 2
        end
        item
          Column = 2
          Control = edValue22
          Row = 2
        end
        item
          Column = 3
          Control = edValue23
          Row = 2
        end
        item
          Column = 4
          Control = edValue24
          Row = 2
        end
        item
          Column = 0
          Control = laLine3
          Row = 3
        end
        item
          Column = 1
          Control = edValue31
          Row = 3
        end
        item
          Column = 2
          Control = edValue32
          Row = 3
        end
        item
          Column = 3
          Control = edValue33
          Row = 3
        end
        item
          Column = 4
          Control = edValue34
          Row = 3
        end
        item
          Column = 0
          Control = laLine4
          Row = 4
        end
        item
          Column = 1
          Control = edValue41
          Row = 4
        end
        item
          Column = 2
          Control = edValue42
          Row = 4
        end
        item
          Column = 3
          Control = edValue43
          Row = 4
        end
        item
          Column = 4
          Control = edValue44
          Row = 4
        end>
      RowCollection = <
        item
          Value = 20.000002261933290000
        end
        item
          Value = 20.001225837430540000
        end
        item
          Value = 19.997856849499670000
        end
        item
          Value = 19.999151827068100000
        end
        item
          Value = 20.001763224068400000
        end>
      TabOrder = 0
      DesignSize = (
        457
        189)
      object laColumn1: TLabel
        Left = 129
        Top = 12
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[1]'
      end
      object laColumn2: TLabel
        Left = 220
        Top = 12
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[2]'
      end
      object laColumn3: TLabel
        Left = 311
        Top = 12
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[3]'
      end
      object laHeader: TLabel
        Left = 44
        Top = 12
        Width = 3
        Height = 13
        Anchors = []
      end
      object laColumn4: TLabel
        Left = 403
        Top = 12
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[4]'
      end
      object laLine1: TLabel
        Left = 38
        Top = 49
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[1]'
      end
      object edValue11: TEdit
        AlignWithMargins = True
        Left = 96
        Top = 46
        Width = 80
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 0
        Text = '1.0'
        OnChange = edValueChange
      end
      object edValue12: TEdit
        AlignWithMargins = True
        Left = 187
        Top = 46
        Width = 80
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 1
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValue13: TEdit
        AlignWithMargins = True
        Left = 278
        Top = 46
        Width = 81
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 2
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValue14: TEdit
        AlignWithMargins = True
        Left = 369
        Top = 46
        Width = 83
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 3
        Text = '0.0'
        OnChange = edValueChange
      end
      object laLine2: TLabel
        Left = 38
        Top = 86
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[2]'
      end
      object edValue21: TEdit
        AlignWithMargins = True
        Left = 96
        Top = 83
        Width = 80
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 4
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValue22: TEdit
        AlignWithMargins = True
        Left = 187
        Top = 83
        Width = 80
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 5
        Text = '1.0'
        OnChange = edValueChange
      end
      object edValue23: TEdit
        AlignWithMargins = True
        Left = 278
        Top = 83
        Width = 81
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 6
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValue24: TEdit
        AlignWithMargins = True
        Left = 369
        Top = 83
        Width = 83
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 7
        Text = '0.0'
        OnChange = edValueChange
      end
      object laLine3: TLabel
        Left = 38
        Top = 123
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[3]'
      end
      object edValue31: TEdit
        AlignWithMargins = True
        Left = 96
        Top = 120
        Width = 80
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 8
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValue32: TEdit
        AlignWithMargins = True
        Left = 187
        Top = 120
        Width = 80
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 9
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValue33: TEdit
        AlignWithMargins = True
        Left = 278
        Top = 120
        Width = 81
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 10
        Text = '1.0'
        OnChange = edValueChange
      end
      object edValue34: TEdit
        AlignWithMargins = True
        Left = 369
        Top = 120
        Width = 83
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 11
        Text = '0.0'
        OnChange = edValueChange
      end
      object laLine4: TLabel
        Left = 38
        Top = 162
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[4]'
      end
      object edValue41: TEdit
        AlignWithMargins = True
        Left = 96
        Top = 159
        Width = 80
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 12
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValue42: TEdit
        AlignWithMargins = True
        Left = 187
        Top = 159
        Width = 80
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 13
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValue43: TEdit
        AlignWithMargins = True
        Left = 278
        Top = 159
        Width = 81
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 14
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValue44: TEdit
        AlignWithMargins = True
        Left = 371
        Top = 159
        Width = 83
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 15
        Text = '1.0'
        OnChange = edValueChange
        ExplicitLeft = 369
      end
    end
  end
end
