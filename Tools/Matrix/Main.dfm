object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'MainForm'
  ClientHeight = 441
  ClientWidth = 454
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PrintScale = poNone
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 13
  object pcMain: TPageControl
    Left = 0
    Top = 0
    Width = 454
    Height = 441
    ActivePage = tsMatrix3x3
    Align = alClient
    TabOrder = 0
    OnChange = pcMainChange
    object tsMatrix3x3: TTabSheet
      Caption = '3x3 Matrix'
      object laVec2DToTransform: TLabel
        Left = 0
        Top = 229
        Width = 446
        Height = 13
        Align = alTop
        Caption = 'Vector to transform'
        ExplicitWidth = 94
      end
      object laTransformMatrix3x3: TLabel
        Left = 0
        Top = 0
        Width = 446
        Height = 13
        Align = alTop
        Caption = 'Transform matrix'
        ExplicitWidth = 82
      end
      object laVec2DResult: TLabel
        Left = 0
        Top = 333
        Width = 446
        Height = 13
        Align = alTop
        Caption = 'Resulting vector'
        ExplicitWidth = 78
      end
      inline mt3x3Matrix: TMatrixTable
        AlignWithMargins = True
        Left = 3
        Top = 16
        Width = 440
        Height = 185
        Align = alTop
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        ExplicitLeft = 3
        ExplicitTop = 16
        ExplicitWidth = 440
        ExplicitHeight = 185
        inherited paBackground: TPanel
          Width = 440
          Height = 185
          ExplicitWidth = 440
          ExplicitHeight = 185
          inherited gpMatrix: TGridPanel
            Width = 436
            Height = 181
            ControlCollection = <
              item
                Column = 1
                Control = mt3x3Matrix.laColumn1
                Row = 0
              end
              item
                Column = 2
                Control = mt3x3Matrix.laColumn2
                Row = 0
              end
              item
                Column = 3
                Control = mt3x3Matrix.laColumn3
                Row = 0
              end
              item
                Column = 0
                Control = mt3x3Matrix.laHeader
                Row = 0
              end
              item
                Column = 4
                Control = mt3x3Matrix.laColumn4
                Row = 0
              end
              item
                Column = 0
                Control = mt3x3Matrix.laLine1
                Row = 1
              end
              item
                Column = 1
                Control = mt3x3Matrix.edValue11
                Row = 1
              end
              item
                Column = 2
                Control = mt3x3Matrix.edValue12
                Row = 1
              end
              item
                Column = 3
                Control = mt3x3Matrix.edValue13
                Row = 1
              end
              item
                Column = 4
                Control = mt3x3Matrix.edValue14
                Row = 1
              end
              item
                Column = 0
                Control = mt3x3Matrix.laLine2
                Row = 2
              end
              item
                Column = 1
                Control = mt3x3Matrix.edValue21
                Row = 2
              end
              item
                Column = 2
                Control = mt3x3Matrix.edValue22
                Row = 2
              end
              item
                Column = 3
                Control = mt3x3Matrix.edValue23
                Row = 2
              end
              item
                Column = 4
                Control = mt3x3Matrix.edValue24
                Row = 2
              end
              item
                Column = 0
                Control = mt3x3Matrix.laLine3
                Row = 3
              end
              item
                Column = 1
                Control = mt3x3Matrix.edValue31
                Row = 3
              end
              item
                Column = 2
                Control = mt3x3Matrix.edValue32
                Row = 3
              end
              item
                Column = 3
                Control = mt3x3Matrix.edValue33
                Row = 3
              end
              item
                Column = 4
                Control = mt3x3Matrix.edValue34
                Row = 3
              end
              item
                Column = 0
                Control = mt3x3Matrix.laLine4
                Row = 4
              end
              item
                Column = 1
                Control = mt3x3Matrix.edValue41
                Row = 4
              end
              item
                Column = 2
                Control = mt3x3Matrix.edValue42
                Row = 4
              end
              item
                Column = 3
                Control = mt3x3Matrix.edValue43
                Row = 4
              end
              item
                Column = 4
                Control = mt3x3Matrix.edValue44
                Row = 4
              end>
            ExplicitWidth = 436
            ExplicitHeight = 181
            inherited laColumn1: TLabel
              Left = 123
              Top = 11
            end
            inherited laColumn2: TLabel
              Left = 210
              Top = 11
            end
            inherited laColumn3: TLabel
              Left = 297
              Top = 11
            end
            inherited laHeader: TLabel
              Left = 42
              Top = 11
            end
            inherited laColumn4: TLabel
              Left = 385
              Top = 11
            end
            inherited laLine1: TLabel
              Left = 36
              Top = 47
            end
            inherited edValue11: TEdit
              Left = 92
              Top = 44
              Width = 77
              ExplicitLeft = 92
              ExplicitTop = 44
              ExplicitWidth = 77
            end
            inherited edValue12: TEdit
              Left = 179
              Top = 44
              Width = 77
              ExplicitLeft = 179
              ExplicitTop = 44
              ExplicitWidth = 77
            end
            inherited edValue13: TEdit
              Left = 266
              Top = 44
              Width = 77
              ExplicitLeft = 266
              ExplicitTop = 44
              ExplicitWidth = 77
            end
            inherited edValue14: TEdit
              Left = 353
              Top = 44
              Width = 78
              ExplicitLeft = 353
              ExplicitTop = 44
              ExplicitWidth = 78
            end
            inherited laLine2: TLabel
              Left = 36
              Top = 83
            end
            inherited edValue21: TEdit
              Left = 92
              Top = 80
              Width = 77
              ExplicitLeft = 92
              ExplicitTop = 80
              ExplicitWidth = 77
            end
            inherited edValue22: TEdit
              Left = 179
              Top = 80
              Width = 77
              ExplicitLeft = 179
              ExplicitTop = 80
              ExplicitWidth = 77
            end
            inherited edValue23: TEdit
              Left = 266
              Top = 80
              Width = 77
              ExplicitLeft = 266
              ExplicitTop = 80
              ExplicitWidth = 77
            end
            inherited edValue24: TEdit
              Left = 353
              Top = 80
              Width = 78
              ExplicitLeft = 353
              ExplicitTop = 80
              ExplicitWidth = 78
            end
            inherited laLine3: TLabel
              Left = 36
              Top = 119
            end
            inherited edValue31: TEdit
              Left = 92
              Top = 116
              Width = 77
              ExplicitLeft = 92
              ExplicitTop = 116
              ExplicitWidth = 77
            end
            inherited edValue32: TEdit
              Left = 179
              Top = 116
              Width = 77
              ExplicitLeft = 179
              ExplicitTop = 116
              ExplicitWidth = 77
            end
            inherited edValue33: TEdit
              Left = 266
              Top = 116
              Width = 77
              ExplicitLeft = 266
              ExplicitTop = 116
              ExplicitWidth = 77
            end
            inherited edValue34: TEdit
              Left = 353
              Top = 116
              Width = 78
              ExplicitLeft = 353
              ExplicitTop = 116
              ExplicitWidth = 78
            end
            inherited laLine4: TLabel
              Left = 36
              Top = 156
            end
            inherited edValue41: TEdit
              Left = 92
              Top = 153
              Width = 77
              ExplicitLeft = 92
              ExplicitTop = 153
              ExplicitWidth = 77
            end
            inherited edValue42: TEdit
              Left = 179
              Top = 153
              Width = 77
              ExplicitLeft = 179
              ExplicitTop = 153
              ExplicitWidth = 77
            end
            inherited edValue43: TEdit
              Left = 266
              Top = 153
              Width = 77
              ExplicitLeft = 266
              ExplicitTop = 153
              ExplicitWidth = 77
            end
            inherited edValue44: TEdit
              Left = 353
              Top = 153
              Width = 78
              ExplicitLeft = 353
              ExplicitTop = 153
              ExplicitWidth = 78
            end
          end
        end
      end
      inline vtVec2DToTransform: TVectorTable
        AlignWithMargins = True
        Left = 3
        Top = 245
        Width = 440
        Height = 60
        Align = alTop
        TabOrder = 2
        ExplicitLeft = 3
        ExplicitTop = 245
        ExplicitWidth = 440
        ExplicitHeight = 60
        inherited paBackground: TPanel
          Width = 440
          Height = 60
          ExplicitWidth = 440
          ExplicitHeight = 60
          inherited gpVector: TGridPanel
            Width = 436
            Height = 56
            ControlCollection = <
              item
                Column = 0
                Control = vtVec2DToTransform.laColumn1
                Row = 0
              end
              item
                Column = 1
                Control = vtVec2DToTransform.laColumn2
                Row = 0
              end
              item
                Column = 2
                Control = vtVec2DToTransform.laColumn3
                Row = 0
              end
              item
                Column = 1
                Control = vtVec2DToTransform.edValueY
                Row = 1
              end
              item
                Column = 0
                Control = vtVec2DToTransform.edValueX
                Row = 1
              end
              item
                Column = 2
                Control = vtVec2DToTransform.edValueZ
                Row = 1
              end>
            ExplicitWidth = 436
            ExplicitHeight = 56
            inherited laColumn1: TLabel
              Left = 65
              Top = 7
            end
            inherited laColumn2: TLabel
              Left = 210
              Top = 7
            end
            inherited laColumn3: TLabel
              Left = 356
              Top = 7
            end
            inherited edValueY: TEdit
              Left = 157
              Top = 32
              ExplicitLeft = 157
              ExplicitTop = 32
            end
            inherited edValueX: TEdit
              Left = 12
              Top = 32
              ExplicitLeft = 12
              ExplicitTop = 32
            end
            inherited edValueZ: TEdit
              Left = 302
              Top = 32
              ExplicitLeft = 302
              ExplicitTop = 32
            end
          end
        end
      end
      inline vtVec2DResult: TVectorTable
        AlignWithMargins = True
        Left = 3
        Top = 349
        Width = 440
        Height = 60
        Align = alTop
        TabOrder = 4
        ExplicitLeft = 3
        ExplicitTop = 349
        ExplicitWidth = 440
        ExplicitHeight = 60
        inherited paBackground: TPanel
          Width = 440
          Height = 60
          ExplicitWidth = 440
          ExplicitHeight = 60
          inherited gpVector: TGridPanel
            Width = 436
            Height = 56
            ControlCollection = <
              item
                Column = 0
                Control = vtVec2DResult.laColumn1
                Row = 0
              end
              item
                Column = 1
                Control = vtVec2DResult.laColumn2
                Row = 0
              end
              item
                Column = 2
                Control = vtVec2DResult.laColumn3
                Row = 0
              end
              item
                Column = 1
                Control = vtVec2DResult.edValueY
                Row = 1
              end
              item
                Column = 0
                Control = vtVec2DResult.edValueX
                Row = 1
              end
              item
                Column = 2
                Control = vtVec2DResult.edValueZ
                Row = 1
              end>
            ExplicitWidth = 436
            ExplicitHeight = 56
            inherited laColumn1: TLabel
              Left = 65
              Top = 7
            end
            inherited laColumn2: TLabel
              Left = 210
              Top = 7
            end
            inherited laColumn3: TLabel
              Left = 356
              Top = 7
            end
            inherited edValueY: TEdit
              Left = 157
              Top = 32
              ExplicitLeft = 157
              ExplicitTop = 32
            end
            inherited edValueX: TEdit
              Left = 12
              Top = 32
              ExplicitLeft = 12
              ExplicitTop = 32
            end
            inherited edValueZ: TEdit
              Left = 302
              Top = 32
              ExplicitLeft = 302
              ExplicitTop = 32
            end
          end
        end
      end
      object btMat3x3Transform: TButton
        Left = 0
        Top = 308
        Width = 446
        Height = 25
        Align = alTop
        Caption = 'Transform'
        TabOrder = 3
        OnClick = btMat3x3TransformClick
      end
      object btMat3x3Inverse: TButton
        Left = 0
        Top = 204
        Width = 446
        Height = 25
        Align = alTop
        Caption = 'Inverse'
        TabOrder = 1
        OnClick = btMat3x3InverseClick
      end
    end
    object tsMatrix4x4: TTabSheet
      Caption = '4x4 Matrix'
      ImageIndex = 1
      object laTransformMatrix4x4: TLabel
        Left = 0
        Top = 0
        Width = 446
        Height = 13
        Align = alTop
        Caption = 'Transform matrix'
        ExplicitWidth = 82
      end
      object laVec3DResult: TLabel
        Left = 0
        Top = 333
        Width = 446
        Height = 13
        Align = alTop
        Caption = 'Resulting vector'
        ExplicitWidth = 78
      end
      object laVec3DToTransform: TLabel
        Left = 0
        Top = 229
        Width = 446
        Height = 13
        Align = alTop
        Caption = 'Vector to transform'
        ExplicitWidth = 94
      end
      object btMat4x4Transform: TButton
        Left = 0
        Top = 308
        Width = 446
        Height = 25
        Align = alTop
        Caption = 'Transform'
        TabOrder = 3
        OnClick = btMat4x4TransformClick
      end
      inline mt4x4Matrix: TMatrixTable
        AlignWithMargins = True
        Left = 3
        Top = 16
        Width = 440
        Height = 185
        Align = alTop
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        ExplicitLeft = 3
        ExplicitTop = 16
        ExplicitWidth = 440
        ExplicitHeight = 185
        inherited paBackground: TPanel
          Width = 440
          Height = 185
          ExplicitWidth = 440
          ExplicitHeight = 185
          inherited gpMatrix: TGridPanel
            Width = 436
            Height = 181
            ControlCollection = <
              item
                Column = 1
                Control = mt4x4Matrix.laColumn1
                Row = 0
              end
              item
                Column = 2
                Control = mt4x4Matrix.laColumn2
                Row = 0
              end
              item
                Column = 3
                Control = mt4x4Matrix.laColumn3
                Row = 0
              end
              item
                Column = 0
                Control = mt4x4Matrix.laHeader
                Row = 0
              end
              item
                Column = 4
                Control = mt4x4Matrix.laColumn4
                Row = 0
              end
              item
                Column = 0
                Control = mt4x4Matrix.laLine1
                Row = 1
              end
              item
                Column = 1
                Control = mt4x4Matrix.edValue11
                Row = 1
              end
              item
                Column = 2
                Control = mt4x4Matrix.edValue12
                Row = 1
              end
              item
                Column = 3
                Control = mt4x4Matrix.edValue13
                Row = 1
              end
              item
                Column = 4
                Control = mt4x4Matrix.edValue14
                Row = 1
              end
              item
                Column = 0
                Control = mt4x4Matrix.laLine2
                Row = 2
              end
              item
                Column = 1
                Control = mt4x4Matrix.edValue21
                Row = 2
              end
              item
                Column = 2
                Control = mt4x4Matrix.edValue22
                Row = 2
              end
              item
                Column = 3
                Control = mt4x4Matrix.edValue23
                Row = 2
              end
              item
                Column = 4
                Control = mt4x4Matrix.edValue24
                Row = 2
              end
              item
                Column = 0
                Control = mt4x4Matrix.laLine3
                Row = 3
              end
              item
                Column = 1
                Control = mt4x4Matrix.edValue31
                Row = 3
              end
              item
                Column = 2
                Control = mt4x4Matrix.edValue32
                Row = 3
              end
              item
                Column = 3
                Control = mt4x4Matrix.edValue33
                Row = 3
              end
              item
                Column = 4
                Control = mt4x4Matrix.edValue34
                Row = 3
              end
              item
                Column = 0
                Control = mt4x4Matrix.laLine4
                Row = 4
              end
              item
                Column = 1
                Control = mt4x4Matrix.edValue41
                Row = 4
              end
              item
                Column = 2
                Control = mt4x4Matrix.edValue42
                Row = 4
              end
              item
                Column = 3
                Control = mt4x4Matrix.edValue43
                Row = 4
              end
              item
                Column = 4
                Control = mt4x4Matrix.edValue44
                Row = 4
              end>
            ExplicitWidth = 436
            ExplicitHeight = 181
            inherited laColumn1: TLabel
              Left = 123
              Top = 11
            end
            inherited laColumn2: TLabel
              Left = 210
              Top = 11
            end
            inherited laColumn3: TLabel
              Left = 297
              Top = 11
            end
            inherited laHeader: TLabel
              Left = 42
              Top = 11
            end
            inherited laColumn4: TLabel
              Left = 385
              Top = 11
            end
            inherited laLine1: TLabel
              Left = 36
              Top = 47
            end
            inherited edValue11: TEdit
              Left = 92
              Top = 44
              Width = 77
              ExplicitLeft = 92
              ExplicitTop = 44
              ExplicitWidth = 77
            end
            inherited edValue12: TEdit
              Left = 179
              Top = 44
              Width = 77
              ExplicitLeft = 179
              ExplicitTop = 44
              ExplicitWidth = 77
            end
            inherited edValue13: TEdit
              Left = 266
              Top = 44
              Width = 77
              ExplicitLeft = 266
              ExplicitTop = 44
              ExplicitWidth = 77
            end
            inherited edValue14: TEdit
              Left = 353
              Top = 44
              Width = 78
              ExplicitLeft = 353
              ExplicitTop = 44
              ExplicitWidth = 78
            end
            inherited laLine2: TLabel
              Left = 36
              Top = 83
            end
            inherited edValue21: TEdit
              Left = 92
              Top = 80
              Width = 77
              ExplicitLeft = 92
              ExplicitTop = 80
              ExplicitWidth = 77
            end
            inherited edValue22: TEdit
              Left = 179
              Top = 80
              Width = 77
              ExplicitLeft = 179
              ExplicitTop = 80
              ExplicitWidth = 77
            end
            inherited edValue23: TEdit
              Left = 266
              Top = 80
              Width = 77
              ExplicitLeft = 266
              ExplicitTop = 80
              ExplicitWidth = 77
            end
            inherited edValue24: TEdit
              Left = 353
              Top = 80
              Width = 78
              ExplicitLeft = 353
              ExplicitTop = 80
              ExplicitWidth = 78
            end
            inherited laLine3: TLabel
              Left = 36
              Top = 119
            end
            inherited edValue31: TEdit
              Left = 92
              Top = 116
              Width = 77
              ExplicitLeft = 92
              ExplicitTop = 116
              ExplicitWidth = 77
            end
            inherited edValue32: TEdit
              Left = 179
              Top = 116
              Width = 77
              ExplicitLeft = 179
              ExplicitTop = 116
              ExplicitWidth = 77
            end
            inherited edValue33: TEdit
              Left = 266
              Top = 116
              Width = 77
              ExplicitLeft = 266
              ExplicitTop = 116
              ExplicitWidth = 77
            end
            inherited edValue34: TEdit
              Left = 353
              Top = 116
              Width = 78
              ExplicitLeft = 353
              ExplicitTop = 116
              ExplicitWidth = 78
            end
            inherited laLine4: TLabel
              Left = 36
              Top = 156
            end
            inherited edValue41: TEdit
              Left = 92
              Top = 153
              Width = 77
              ExplicitLeft = 92
              ExplicitTop = 153
              ExplicitWidth = 77
            end
            inherited edValue42: TEdit
              Left = 179
              Top = 153
              Width = 77
              ExplicitLeft = 179
              ExplicitTop = 153
              ExplicitWidth = 77
            end
            inherited edValue43: TEdit
              Left = 266
              Top = 153
              Width = 77
              ExplicitLeft = 266
              ExplicitTop = 153
              ExplicitWidth = 77
            end
            inherited edValue44: TEdit
              Left = 353
              Top = 153
              Width = 78
              ExplicitLeft = 353
              ExplicitTop = 153
              ExplicitWidth = 78
            end
          end
        end
      end
      inline vtVec3DResult: TVectorTable
        AlignWithMargins = True
        Left = 3
        Top = 349
        Width = 440
        Height = 60
        Align = alTop
        Constraints.MaxWidth = 440
        Constraints.MinWidth = 440
        TabOrder = 4
        ExplicitLeft = 3
        ExplicitTop = 349
        ExplicitWidth = 440
        ExplicitHeight = 60
        inherited paBackground: TPanel
          Width = 440
          Height = 60
          ExplicitWidth = 440
          ExplicitHeight = 60
          inherited gpVector: TGridPanel
            Width = 436
            Height = 56
            ControlCollection = <
              item
                Column = 0
                Control = vtVec3DResult.laColumn1
                Row = 0
              end
              item
                Column = 1
                Control = vtVec3DResult.laColumn2
                Row = 0
              end
              item
                Column = 2
                Control = vtVec3DResult.laColumn3
                Row = 0
              end
              item
                Column = 1
                Control = vtVec3DResult.edValueY
                Row = 1
              end
              item
                Column = 0
                Control = vtVec3DResult.edValueX
                Row = 1
              end
              item
                Column = 2
                Control = vtVec3DResult.edValueZ
                Row = 1
              end>
            ExplicitWidth = 436
            ExplicitHeight = 56
            inherited laColumn1: TLabel
              Left = 65
              Top = 7
            end
            inherited laColumn2: TLabel
              Left = 210
              Top = 7
            end
            inherited laColumn3: TLabel
              Left = 356
              Top = 7
            end
            inherited edValueY: TEdit
              Left = 157
              Top = 32
              ExplicitLeft = 157
              ExplicitTop = 32
            end
            inherited edValueX: TEdit
              Left = 12
              Top = 32
              ExplicitLeft = 12
              ExplicitTop = 32
            end
            inherited edValueZ: TEdit
              Left = 302
              Top = 32
              ExplicitLeft = 302
              ExplicitTop = 32
            end
          end
        end
      end
      inline vtVec3DToTransform: TVectorTable
        AlignWithMargins = True
        Left = 3
        Top = 245
        Width = 440
        Height = 60
        Align = alTop
        TabOrder = 2
        ExplicitLeft = 3
        ExplicitTop = 245
        ExplicitWidth = 440
        ExplicitHeight = 60
        inherited paBackground: TPanel
          Width = 440
          Height = 60
          ExplicitWidth = 440
          ExplicitHeight = 60
          inherited gpVector: TGridPanel
            Width = 436
            Height = 56
            ControlCollection = <
              item
                Column = 0
                Control = vtVec3DToTransform.laColumn1
                Row = 0
              end
              item
                Column = 1
                Control = vtVec3DToTransform.laColumn2
                Row = 0
              end
              item
                Column = 2
                Control = vtVec3DToTransform.laColumn3
                Row = 0
              end
              item
                Column = 1
                Control = vtVec3DToTransform.edValueY
                Row = 1
              end
              item
                Column = 0
                Control = vtVec3DToTransform.edValueX
                Row = 1
              end
              item
                Column = 2
                Control = vtVec3DToTransform.edValueZ
                Row = 1
              end>
            ExplicitWidth = 436
            ExplicitHeight = 56
            inherited laColumn1: TLabel
              Left = 65
              Top = 7
            end
            inherited laColumn2: TLabel
              Left = 210
              Top = 7
            end
            inherited laColumn3: TLabel
              Left = 356
              Top = 7
            end
            inherited edValueY: TEdit
              Left = 157
              Top = 32
              ExplicitLeft = 157
              ExplicitTop = 32
            end
            inherited edValueX: TEdit
              Left = 12
              Top = 32
              ExplicitLeft = 12
              ExplicitTop = 32
            end
            inherited edValueZ: TEdit
              Left = 302
              Top = 32
              ExplicitLeft = 302
              ExplicitTop = 32
            end
          end
        end
      end
      object btMat4x4Inverse: TButton
        Left = 0
        Top = 204
        Width = 446
        Height = 25
        Align = alTop
        Caption = 'Inverse'
        TabOrder = 1
        OnClick = btMat4x4InverseClick
      end
    end
  end
end
