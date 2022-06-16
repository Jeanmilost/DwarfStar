inherited VectorTable: TVectorTable
  Width = 575
  Height = 70
  object paBackground: TPanel
    Left = 0
    Top = 0
    Width = 575
    Height = 70
    Align = alClient
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    object gpVector: TGridPanel
      AlignWithMargins = True
      Left = 1
      Top = 1
      Width = 571
      Height = 66
      Margins.Left = 1
      Margins.Top = 1
      Margins.Right = 1
      Margins.Bottom = 1
      Align = alClient
      BevelOuter = bvNone
      ColumnCollection = <
        item
          Value = 33.343643058000630000
        end
        item
          Value = 33.313481592439750000
        end
        item
          Value = 33.342875349559620000
        end>
      ControlCollection = <
        item
          Column = 0
          Control = laColumn1
          Row = 0
        end
        item
          Column = 1
          Control = laColumn2
          Row = 0
        end
        item
          Column = 2
          Control = laColumn3
          Row = 0
        end
        item
          Column = 1
          Control = edValueY
          Row = 1
        end
        item
          Column = 0
          Control = edValueX
          Row = 1
        end
        item
          Column = 2
          Control = edValueZ
          Row = 1
        end>
      RowCollection = <
        item
          Value = 50.000000000000000000
        end
        item
          Value = 50.000000000000000000
        end>
      TabOrder = 0
      DesignSize = (
        571
        66)
      object laColumn1: TLabel
        Left = 88
        Top = 10
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[1]'
      end
      object laColumn2: TLabel
        Left = 278
        Top = 10
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[2]'
      end
      object laColumn3: TLabel
        Left = 468
        Top = 10
        Width = 14
        Height = 13
        Anchors = []
        Caption = '[3]'
      end
      object edValueY: TEdit
        AlignWithMargins = True
        Left = 224
        Top = 40
        Width = 121
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
      object edValueX: TEdit
        AlignWithMargins = True
        Left = 34
        Top = 40
        Width = 121
        Height = 19
        Margins.Left = 5
        Margins.Top = 0
        Margins.Right = 5
        Margins.Bottom = 0
        Anchors = []
        TabOrder = 0
        Text = '0.0'
        OnChange = edValueChange
      end
      object edValueZ: TEdit
        AlignWithMargins = True
        Left = 415
        Top = 40
        Width = 121
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
    end
  end
end
