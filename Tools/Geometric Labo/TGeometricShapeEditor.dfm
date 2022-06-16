object GeometricShapeEditor: TGeometricShapeEditor
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Shape editor'
  ClientHeight = 246
  ClientWidth = 400
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PrintScale = poNone
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pcPages: TPageControl
    Left = 0
    Top = 0
    Width = 400
    Height = 211
    ActivePage = tsLine
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object tsLine: TTabSheet
      Caption = 'tsLine'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paLineHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object imLine: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A000002B54944415478DAED
            DC4B6E134110C6F16EEF085C812577488C7808CC1884C235D8701E24CE817844
            246285E00C486C90388357B8F117470CC1AF79747755777DFFCD54D7AAA4DF7E
            BC63A21DCF9E3E9CB8F0267877E4837BE5A50FB2DCB4691E85A57FBB1A8FD69B
            F08B20426D625CF68320026DC7088B49F0CF0992B9BB8FE7F796DEBD5F8DB7DA
            6D5804E75F7C3B3F3B2748C60E61E045904C75C14004C950570C4490C4F5C140
            0449585F0C4490440DC1400449D0500C4490C88DC1400489D8580C449048C5C0
            400489502C0C449091C5C4400419516C0C449081A5C0400419502A0C44909EA5
            C44004E9516A0C44908EE5C04004E9502E0C4490034D9BE67E58FA772E030622
            C89E72632082EC48020311644B52188820FF25898108F24FD21888205769C040
            04717A309079104D18C83488360C64164423063209A215039903D18C814C8168
            C74066404AC04026404AC140D583948481AA06290D03550B522206AA12A4540C
            541D48C918A82A90D2315035203560A02A406AC140C583D484818A06A90D0315
            0B5223062A12A4560C541C48CD18A82890DA3150312016305011205630907A10
            4B18483588350CA416C422065209621503A903B18C81548158C7406A4088B14E
            050831DAC44188713D5110626C2606428CED8980106377D94188B1BFAC20C438
            5C361062742B0B0831BA971C8418FD4A0A7285813FB1DD6CB7C4D8573210620C
            2B09083186171D8418E38A0A428CF1450321469CA28010235EA3418811B75120
            C488DF601062A469100831D2D51B841869EB05428CF4750621469E3A8110235F
            07418891B7BD20C4C8DF4E1062C8B4158418726D801043B66B20C490EF2F0831
            747409420C3DF99327CF1EB8F0FBC36ABCD1AEC3C2F9C9E9D74F1F2FA40FB496
            3F99CDBFAFBE77DA153124F3D3D9FC6770EEF6FA490CE9FC71D39CFAE05FBBE0
            1693E05E7EB938FB2C7D94E5FE00AA77BBF3AFBE00240000000049454E44AE42
            6082}
        end
        object laLineTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 153
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Line editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paLineValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        object paLinePoint: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 20
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 20
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laLinePointCaption: TLabel
            Left = 0
            Top = 0
            Width = 24
            Height = 13
            Align = alLeft
            Caption = 'Point'
            Layout = tlCenter
          end
          inline gvLinePoint: TGeometricVectorFrame
            Left = 24
            Top = 0
            Width = 358
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 24
            ExplicitWidth = 358
            inherited paMain: TPanel
              Width = 358
              ExplicitWidth = 358
              inherited laX: TLabel
                Left = 50
                ExplicitLeft = 50
              end
              inherited laY: TLabel
                Left = 161
                ExplicitLeft = 161
              end
              inherited laZ: TLabel
                Left = 272
                ExplicitLeft = 272
              end
              inherited edX: TEdit
                Left = 61
                ExplicitLeft = 61
              end
              inherited edY: TEdit
                Left = 172
                ExplicitLeft = 172
              end
              inherited edZ: TEdit
                Left = 283
                ExplicitLeft = 283
              end
            end
          end
        end
        object paLineDir: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 46
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laLineDirCaption: TLabel
            Left = 0
            Top = 0
            Width = 42
            Height = 13
            Align = alLeft
            Caption = 'Direction'
            Layout = tlCenter
          end
          inline gvLineDir: TGeometricVectorFrame
            Left = 42
            Top = 0
            Width = 340
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 42
            ExplicitWidth = 340
            inherited paMain: TPanel
              Width = 340
              ExplicitWidth = 340
              inherited laX: TLabel
                Left = 32
                ExplicitLeft = 32
              end
              inherited laY: TLabel
                Left = 143
                ExplicitLeft = 143
              end
              inherited laZ: TLabel
                Left = 254
                ExplicitLeft = 254
              end
              inherited edX: TEdit
                Left = 43
                ExplicitLeft = 43
              end
              inherited edY: TEdit
                Left = 154
                ExplicitLeft = 154
              end
              inherited edZ: TEdit
                Left = 265
                ExplicitLeft = 265
              end
            end
          end
        end
      end
    end
    object tsRay: TTabSheet
      Caption = 'tsRay'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paRayHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object imRay: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A0000062D4944415478DAED
            DD498C145518C0F1EFAB19820212014D4671411D45625CD0E0740F633232BD0D
            516382E04141878BB2B85C34EE17F783C6B8801A2F885B24465184AEA5652E76
            B7F1A21E3CB91C8C3126264613203A547FBEAFBBC1EA198AE9A5AA5E2DEF9F74
            A6E64157BFEADF54F7542FD3082AA9AD1ECB5F47086F89D33C24D88EB22794E4
            5299C228027D2E16E73546E8570522A926C63EB138DF31FCA30291D08931E808
            6A70830209B8A14C6144033A201617FC3F4A4708F0A6AAA55B0A24C09A18FBC5
            E2698EE17F04C2BAB2A5F37D092890804A65B3AB9134DE335C3138051240ED62
            700AC4E75C30FE05A2759592B16FFAFF57203E965E931B060D8BD02606A7407C
            CA0D8334BAA56A189FB99D4F81F850B7189C02F1B85E303805E261C363853421
            31C642C770DB189C02F128570CC4F555B3F869BBEB51201EE41506A7407A6C28
            97BB46ABA12916173986BBC2E014480F798DC129902E73C31057E886B2A5EFED
            76BD0AA48B526BF257A30616788CC129900E6B62F09EB1D8313C05441B2A25E3
            935ED7AF403AC86F0C4E81B4593A33BE12A0C63753BE61700AA48D82C2E014C8
            2CB96220DE5A318B1F7B7D790AE424B960D848747BB9647CE0C7652A109786B3
            D9AB8834C658E218F61583532027C80D43DC4C6D143753EFFB79D90A645A3231
            3805E2483606A7409AB962006CAA58FA7B41CD43818846F2F92B6D1B4A201983
            4B3C0863D46CB008E00CC7B04D4477544BC6BB41CF27D12061C3E0120B323456
            B8A20FA914260C2E91206E18887867D92CBE23736E89030933069728905426B3
            02A1EF0BB138E0180E0D06971890742E7729D4F020CCC08089B2A9EF963DBF63
            2502242A185CEC41A284C1C51AC40D439C368B23F0B765CFEF44C516A489C177
            E06739866BE23411560C2E9620ABAF2F2CAFF511EF192D18E2A06FB338E8DB25
            7B7E272B762051C6E0620512750C2E36204D0CBECF38DB314C40B8A5522ABE21
            7B7EED160B90B860709107B9766CED257D68F3CD540B06216CAD9AFAEBB2E7D7
            699106891B06175910570CA06D55CBD8297B7EDD164990A16CF6628DB4498819
            0617399006063F1C824B1DC3B1C0E02205E2868184DBCBA5E20ED9F3F3A2C880
            2401838B04485230B8D083A4F3F941B069723A8698F93D15537F4DF6FCBC2ED4
            20A94261194ED14131CB658EE1D86270A105492206174A90E1356BCF27B42767
            6000DC5BB1F45765CFCFCF420792640C2E54206E18E2A0EF3E71D0F78AECF905
            516840EA185AFDB1A90B1CC389C2E042013292C99C6743DF24241C83930EE286
            210EFAEE17077D2FCB9E5FD049055118339306E2820188F050D9D49F977DC5C8
            4A0A4803A35FDC81D3852D93493846FD3A08FA02DD30C4F70F572CE339D95788
            EC02055118B31718C8AA5CEEDCFE1A3FEDAA304E5620200D8CFAABD02F6AF907
            C2472AA5E2B3B2AF8430E53B88C2E82C5F41DC3008E1D1AAA93F237BE3C3986F
            2043A3E3E768FDB54950181DE50B481383F78C41E7B8C2983DCF415C31801EAB
            5AC6D3B23738EC790AA2307ACF339055A36B07FAFB6D7E4BC08AD60BC0C7CB56
            F129D91B1A953C015118DED502323A3ADA3F8573971F9D43A7CC76C6398847FF
            26FAE154DB5EA0213F1CD28A216EA79EA894F427656F60D43A0682A94CEE6EF1
            13CD3FCD8B3B383F7F5AE5616AFD9400B567F4501D249DC9F3FBB6377AB246B5
            67F414A6B385F540F461F3FBDF88E025D4F0E7D9CE287E735AA2113E40CE070B
            1546CFA1D83BAAE2EB9038FD7554A3CBBF368C5FDA3DF3E0F8F8DC33A7EC9FC4
            6AF88D335387345AF49D611C92BD51518E41F80A9C274EBB2B96BEA9D31588FB
            9E2DE23EA3FE0A74C4DACAB2697E237BA3A21C83F0AB02F92668873878DBD6E9
            0A5263B9DB10B1FEC7BF086B2355D3FC52F64645390512B21448C85220214B81
            842C0512B21448C8522021EB380802EC2C5BFAD64E57A040BC8D41FE145F4F17
            A7BDE248FDE64E57901ACB3F8808F5D7E3D648BBECABD281EF656F5494C37436
            BF5FDC5E8D43E3A37DF215B3586AF7CCCD773DF1636103620FFB63E9A285037B
            F6ECB1656F5494C3E6E7BBF2953A071A7FD3769F18FE7DD63302CC17F73B378A
            C5858DEFE9AEB265BC297B83A2DEB1E743B68B2F2F4203A58BB5E02EB1674D40
            E3DDB2AA1E3AFE146EF3532DF9B98C6198F60CA04B87C5E95BB18217C42F031F
            C9DE90B8F41F71C77EF53EFDA5080000000049454E44AE426082}
        end
        object laRayTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 147
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Ray editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paRayValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        object paRayPos: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 20
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 20
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laRayPosCaption: TLabel
            Left = 0
            Top = 0
            Width = 37
            Height = 13
            Align = alLeft
            Caption = 'Position'
            Layout = tlCenter
          end
          inline gvRayPos: TGeometricVectorFrame
            Left = 37
            Top = 0
            Width = 345
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 37
            ExplicitWidth = 345
            inherited paMain: TPanel
              Width = 345
              ExplicitWidth = 345
              inherited laX: TLabel
                Left = 37
                ExplicitLeft = 37
              end
              inherited laY: TLabel
                Left = 148
                ExplicitLeft = 148
              end
              inherited laZ: TLabel
                Left = 259
                ExplicitLeft = 259
              end
              inherited edX: TEdit
                Left = 48
                ExplicitLeft = 48
              end
              inherited edY: TEdit
                Left = 159
                ExplicitLeft = 159
              end
              inherited edZ: TEdit
                Left = 270
                ExplicitLeft = 270
              end
            end
          end
        end
        object paRayDir: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 46
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laRayDirCaption: TLabel
            Left = 0
            Top = 0
            Width = 42
            Height = 13
            Align = alLeft
            Caption = 'Direction'
            Layout = tlCenter
          end
          inline gvRayDir: TGeometricVectorFrame
            Left = 42
            Top = 0
            Width = 340
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 42
            ExplicitWidth = 340
            inherited paMain: TPanel
              Width = 340
              ExplicitWidth = 340
              inherited laX: TLabel
                Left = 32
                ExplicitLeft = 32
              end
              inherited laY: TLabel
                Left = 143
                ExplicitLeft = 143
              end
              inherited laZ: TLabel
                Left = 254
                ExplicitLeft = 254
              end
              inherited edX: TEdit
                Left = 43
                ExplicitLeft = 43
              end
              inherited edY: TEdit
                Left = 154
                ExplicitLeft = 154
              end
              inherited edZ: TEdit
                Left = 265
                ExplicitLeft = 265
              end
            end
          end
        end
      end
    end
    object tsSegment: TTabSheet
      Caption = 'tsSegment'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paSegmentHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object imSegment: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A000007AD4944415478DAED
            9D6B6C53551CC0FFA78F75B0395660422462428C26CE91E0D4B563C4C2BA8D8A
            E80097C8CB84F880A15F40403F681CE21714900F3A159F2822503019AFAD2FB2
            0FB2D6188C2F4C34463FF8811016262363766DEFF17F6ECB689BF5B53ECEBDED
            F92537FDDF7B72CE3DFFF3DBBDE7DEB6EB2520C819E696A51D00741B505A0740
            A6A451E51A057A1E24F29AEF9CE307B681F04EA24820666BDB417C5D3FC9FA01
            5CB67ADD8E7785901C60B2B6761220DD91D56BB89C4447A3292B52A90608791C
            232D2E012A814908C9128BC5A2F3EB0C97319C8ECBA5A086367CEF74FE936E7D
            3CCD35E329CE81A1164F5F6785902C59B8B8AD56D2C2AFE135BADDEB76EEC9B4
            8D466B5B0F056047CA90109225A6969685846ABE6531A5749DCFE3FC2AD33650
            48370AE964B1109225B9108273D07B38076D66B11092254288C21042148610A2
            308410852184280C21446108210AC36CB52D0090E4776A29814E9FCBF141A66D
            345A971EA240D7623822846489C562A9F4EB0C57302CC7BBED3FAE1BABEA2EDA
            ED63E9D66FB25AE78640FB0B8655B87885902C616F2E8EE9CA2FE25FF83D914D
            9730DE45886630555D02741EA5B005C3596C9D025925846441E49DDEC3187664
            DB16A1F0F980C7B141089924F5F5F5FAB2E9358771267F32AE2804E1CF37D202
            050C524A5EF57AFA0E803C0D093286C9D01B677E8D83B72A7A3B21E00A4AC1D5
            04F473402BE9533614D28ECE9D5EF9BBDD6E0F8DB7C13B39B5211F19C6994730
            5C195B429C30725BBBD76B4FFD49611284900C906554CF388A87C28AD892DCC8
            905BE29DA45A28840CB935DE89AA81C869EA1886ED71450E43D0DFDEDFDFFF5F
            AEF62584A4A0B6A3A3AC6A68F8281440064308494212197D286345AE65308490
            044464B0D3D41371457993C110422680C99836346C8F7C35E716047A0D01FFCA
            7CC908EF4210034F19E1DD08C64926A35AA759D1DBDBEBCF771F849008F29C71
            F5FA71207479F476F6F54EA35EBBB21032184208284706A3E48544AEA64E60F8
            585CD1996ABD66552165304A5A88CD6633FC1B908E834264304A56481219DF8C
            0D0D3E75E1C285008F7E95A490880C769A5A1657C45506A3E48498CD1D5348E5
            700FA5D012BD1D2F754F04860657F394C12829214C06540C9FC4D01ABD5D2932
            18252324910C20E4F8D8D52B6B942043EE0EEF0E1482FAE5CBA7968D8EF5C004
            320C81FF56F7F7F70779F771BC4BBC3B906F2232D891D11C57643704FD6B9424
            8351D44264193702A7F00E7C495C912265308A56481219C750C65A25CA6014A5
            10B5CA60149D1026433F3A761A135B1C57A478198CA212924806AE1F2D0BFAD7
            295D46A4AFC5C1FCD6D68AA91239A5661991FEAA1F26A34222A731B4446FA784
            1E290F8CAD578B0C86EA8514930C86AA8524937167F5B475D1DF2A570BAA1512
            960167308547621262FFF8B2C8FC0C747549BCFB3819542924910C0AF099AFC9
            FCAC5A65305427A4C166ABD204A43E0CCD71459F7A9BCCCFA95906435542EAAD
            D6697AD0F41120A6B8A2A290C1508D905290C150851026A30CB4EC77091B627B
            4F3FF12E6C7CBE5864C829F1EE402A4A49869C16EF0E2423910CBCB4FD182F6D
            37169B0C3937DE1D48842C83689D782DFB704C878B58869C1FEF0E4C84C562A9
            F6EB0D8E7819789FF111DE676C2A56190CC5092965190C45099165E80C4E0C1F
            8ADE2ECB703B3686C3E246314212C9C02E1EF0BAFB364109C890B3E5DD018690
            119531EF0E846594BB70CC1F8CED19FDD0EB72B29FDF2E191972DA3C77DEB46C
            9931E40F39858CA8D479ED38A10C80FD5EB7632B94A00C0617214C86E40FBA70
            C4EBE38A988C2DBC0785270517B2C866AB0906243786F3E3BAF20E4EE05B790F
            086F0A2A242C23E4C1DDD6C57543C88850302189641002FB065C8E97780F8452
            28881021237DF22EA4B1B5F5762A813B5E06A5B0D7E7716CE33D004A23AF42C2
            32081E19707FF4762123317913924806EE720F4EE0DB7927AE54F22244C8983C
            391722CBA0E41CDE67D7C696D0B7BD6EE70EDE092B9D9C0A69686E9EA5D1E83C
            42C6E4C999904432F0D2F62DBCB47D9977A26A212742641944770EC3FB621A17
            32322646087BFC428018EE0DEA6979AA8A7A4282C394FE392514AA9C480605D8
            ED733B5EE19DA0DAB8298498ACAD9B08903721FCD4E37461BF2735125F07DBD9
            39E0EEEBE29D9C1A918598AD6D5FC0E41FCE1E0305DAE5733B77F24E4CAD1073
            CBD20EBC753E1659BF8477D1FB8986FC9DAA220EFC0C0D25DBF175DEADD6E075
            AFCBF106EFA4D40CC1A3C307E1AF6A5E0B6A685D260F67BFDB6633D404427F61
            3377E06A6044438D3F3B9D23BC9352334C081BC0A9B87CE9753B9ECEB4019C7B
            3A71CEE8961B23D2820197EB47DE49A9192644FEEC1A4F3DDD78EE7F21D3064C
            CDAD6B092187E43688D4E473B9CEF34E4ACD08210A430851184288C210421486
            10A2308410852184288C712104E0FD01B76373A60D0821B9850919C2D76A5C7A
            F04EBD3DD3064CCD6D3B0881DD2C96A8A6F63B4FEF6FBC935233C4DCD27616CF
            5736604F3926A4CDEBEAF3A45BB971C9A377514D88BD17369B3DF5788EB16AB6
            1A7F12494910D392B6078806D8A0B2A71BB3C13C8D9B2FA7AC085081F30E7B22
            4D55789D6E1C703B0FF04E48EDDCFC3CE4457CD90761299368851CC4236B0394
            E8FF74E492F18F70CD56DB029C057661D8888B318DBA3770F9091BD88B170327
            7827522CFC0F4B9BF2E10EA844230000000049454E44AE426082}
        end
        object laSegmentTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 221
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Segment editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paSegmentValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        object paSegmentStart: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 20
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 20
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laSegmentStartCaption: TLabel
            Left = 0
            Top = 0
            Width = 24
            Height = 13
            Align = alLeft
            Caption = 'Start'
            Layout = tlCenter
          end
          inline gvSegmentStart: TGeometricVectorFrame
            Left = 24
            Top = 0
            Width = 358
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 24
            ExplicitWidth = 358
            inherited paMain: TPanel
              Width = 358
              ExplicitWidth = 358
              inherited laX: TLabel
                Left = 50
                ExplicitLeft = 50
              end
              inherited laY: TLabel
                Left = 161
                ExplicitLeft = 161
              end
              inherited laZ: TLabel
                Left = 272
                ExplicitLeft = 272
              end
              inherited edX: TEdit
                Left = 61
                ExplicitLeft = 61
              end
              inherited edY: TEdit
                Left = 172
                ExplicitLeft = 172
              end
              inherited edZ: TEdit
                Left = 283
                ExplicitLeft = 283
              end
            end
          end
        end
        object paSegmentEnd: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 46
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laSegmentEndCaption: TLabel
            Left = 0
            Top = 0
            Width = 18
            Height = 13
            Align = alLeft
            Caption = 'End'
            Layout = tlCenter
          end
          inline gvSegmentEnd: TGeometricVectorFrame
            Left = 18
            Top = 0
            Width = 364
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 18
            ExplicitWidth = 364
            inherited paMain: TPanel
              Width = 364
              ExplicitWidth = 364
              inherited laX: TLabel
                Left = 56
                ExplicitLeft = 56
              end
              inherited laY: TLabel
                Left = 167
                ExplicitLeft = 167
              end
              inherited laZ: TLabel
                Left = 278
                ExplicitLeft = 278
              end
              inherited edX: TEdit
                Left = 67
                ExplicitLeft = 67
              end
              inherited edY: TEdit
                Left = 178
                ExplicitLeft = 178
              end
              inherited edZ: TEdit
                Left = 289
                ExplicitLeft = 289
              end
            end
          end
        end
      end
    end
    object tsPlane: TTabSheet
      Caption = 'tsPlane'
      ImageIndex = 6
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paPlaneHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object imPlane: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A000006DC4944415478DAED
            9D7D6C136518C09FF7D66D84F1B1C180100DFE81A28221E8305B0B98865E3FC6
            4624042511A3F8079A880A7E4645604685040D09060D242448A2F163212120E9
            AE1FD844B276E05043E4239818A3C198094360C176ED3D3ED75D471D15AE5BE1
            DEA4CF2FB9DCFB5EDFF7DEF79E5FEF7ABDBBBE159047837B717D5545EA7910D0
            4AD9BB69AA81C2A401C421BD523CD2150C5E048B383DFE0008DC45756FB35AA7
            00FFD0B4231ED15E2CA692530DBC0A80EB293976046D9F47C49712D1D01EAB15
            DC6EB723E9A836CA2FA3A9CA5CDC27004EE9800774CC6C3F128D9ECB95175783
            E55B0242ECA664ADE5EE09581B0F6BDBAC1677A9FED30830630401194457706E
            5728D46DA56CA3C73345118EB394544AD0745F753A591B8BC5D216B7F961DAE6
            7DD729D28B42AC4C843BF61B99AC1053C6DE623B8C025625C2DA2EABE59DAAFF
            18CDEE2F41501021332B11899CB452787E4B4B5D2699FE8392D5236D9802F657
            E77CE714686BD3AD946F52FD2AD509DFA05886A42C35A48805CDCD93D2FDFA19
            5A387E4821DA8DC4DFFF138F7E012294ECED79B9BBBBBBDFEAC6B8BCDE393A2A
            5BA9EE1DC30F89DE2750D9D119EDF8B8985A2E8F6F196DF41BB44DD68F00D76E
            F79F42C1B73A43A1434554124EAF7F3D202CA7E428733D461F260C29D79BC1F4
            5D828EEB6F93F60D792FF450E527E2514D336A0EBFF3CC7510F3BC8166FA3CDA
            4301AEBFBA14360A3A8C7C4FC939796503F1488766778FCB0192B248473C98CB
            D3A1ADDB107219CCB3A9ECF131A24D06DE336E1546FC8D33AC3A337FC958901F
            FC53743A79AFDDBD2C27869C79220BB1198AFF2918F8CE67C042EC868548060B
            910C162219147FE35BBC6A667F652136D3E8699EA9087D07256B1484570C2157
            28637EA5871F484829AE3531C34434797DDB048A17B21914AB8BBD46C49496EC
            D5DE795EEFDC0C629FD5ABA7CCCD438C7C154C29612192C14224838548060B91
            0C1622192C4432588864B0109B71BBDDA39295D5CF802E46830377B2109B71AA
            819D00F8B49146806FB2425C3EDFE4AA542A158BC52ED8DDC172C3A9FA4FD02C
            77853D2D9A3CFED78480CD94E9273B2B3A23DA5EBB3B594E14BA41653C2C6D3E
            802CBE8B473A1EB4BB93E504DF31940C1622192C4432588864B010C9602192C1
            4224838548060B910C1622192C4432588864B010C9A0F81B4F8BDE6366751662
            332E35F02902AE30B3475988CD34A8EAF82A70BC4E47AB316905B7E47E963B30
            AA8080CE78589B677727CB19E152FD4FD12EB29DD25784828F16396C045362B2
            F7D48D2184626EB76E754015E6E6C14F9D48060B910C1622192C4432588864B0
            10C9602192C142248385D8CC7C559D96818A0FC8C41801FA9B2CC4669C9EC07E
            10B8D8CC9E160D0D0D9555B5135B5088CB898816051E6FF19652E806D5679478
            6C200B1BE251ED1DBB3B594E14129284C131C9F1783C129A6D7727CB09BE852B
            192C4432588864B010C9602192C14224838548060B910C1622192C4432588864
            B010C960219241F13F4EB3FBCC6C8A85D88C4BF5BF4B02D699D97616623FC2E9
            F1193708475FAA1BB7CF10F2332D9C6EBE789084B4DADDC3724634F97C8D22A3
            6CA2745FA6425F732414FAC5EE4E9533FC908364B010C9602192C14224838548
            060B910C1622192C4432588864B0109B71F97C0FA12E3EA7640D4DCFB2109B71
            AA81C300981BCEA4472CF0FBA76674588B007DD5FDC9ADB158ECB2DD9D2C270A
            DDA04A50A2319B15624F3CDCB1D2EE4E961385846428A1980B4EC423DA2CBB3B
            594EF02D5CC970A9FED324608699CD0A313E336ACC05E748C824E09FB5DD2A72
            E395D599F94BC6826394B8FA1FEA08CDF1A8D661774FCB01DA3B5AE89DFF752E
            4FA7BCDDC2A506DA1070635EB91ED4F1C9C4A1902185F7949B833170DC229A7F
            4201AE1F5C8AB04134B817D757395267285B3BA4D279AA57E04FC23083885D58
            55B1BA2B18BC68B507D9DF63A3633B089C699CCE0D6F3B30499D6EA73DB80D8A
            78B30C7CF9CADEA69E3AFC18E205DAEE2D8968E8CB626A51E057E908AB851063
            F3D665C47AC290A2BD5001776603E3F4F896508C8C3F0353AC362410367546B5
            7556CB3BBD8176405C36FC80E4B50DD0DA19D10E5A6E5BF59F8511C91824E5A8
            546EFF3618ECB152D8B5B0793A2AFA19B8F115910C0AB13411EED83F58D094B2
            1BAEDD530A82023F4C84436B8A084A9066811204C5D835962722DA57960AB7B5
            29CEC371DADB617C299AD6D3CAB4AE58F0772B851B3D81D98AC01F6F50AC9764
            AC34641899FF98330E5FD58EFEE7A8DD561C18DCB7A6C00AE825D19D56F4A547
            43A1DFAC6E49D342FF0342812F2879D70802D24FD3BE8B75E31EFFA9BD3D65B9
            6D8F6F051D32B65172E208DAEEA3CFDACD8948E8BD622A39D5C0FB14328A298C
            CA5F17C5F0241D660E64F4F44747A2D173B917FE0531C73269550D0E0A000000
            0049454E44AE426082}
        end
        object laPlaneTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 172
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Plane editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paPlaneValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        object paPlaneAB: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 20
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 20
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laPlaneACaption: TLabel
            AlignWithMargins = True
            Left = 5
            Top = 0
            Width = 50
            Height = 21
            Margins.Left = 5
            Margins.Top = 0
            Margins.Right = 5
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'A'
            Layout = tlCenter
            ExplicitLeft = 2
          end
          object laPlaneBCaption: TLabel
            AlignWithMargins = True
            Left = 206
            Top = 0
            Width = 50
            Height = 21
            Margins.Left = 25
            Margins.Top = 0
            Margins.Right = 5
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'B'
            Layout = tlCenter
            ExplicitLeft = 208
          end
          object edPlaneB: TEdit
            Left = 261
            Top = 0
            Width = 121
            Height = 21
            Align = alRight
            TabOrder = 1
            OnChange = edPlaneBChange
          end
          object edPlaneA: TEdit
            Left = 60
            Top = 0
            Width = 121
            Height = 21
            Align = alRight
            TabOrder = 0
            OnChange = edPlaneAChange
          end
        end
        object paPlaneCD: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 46
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laPlaneCCaption: TLabel
            AlignWithMargins = True
            Left = 5
            Top = 0
            Width = 50
            Height = 21
            Margins.Left = 5
            Margins.Top = 0
            Margins.Right = 5
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'C'
            Layout = tlCenter
            ExplicitLeft = 2
            ExplicitTop = -2
          end
          object laPlaneDCaption: TLabel
            AlignWithMargins = True
            Left = 206
            Top = 0
            Width = 50
            Height = 21
            Margins.Left = 25
            Margins.Top = 0
            Margins.Right = 5
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'D'
            Layout = tlCenter
            ExplicitLeft = 203
            ExplicitTop = -5
          end
          object edPlaneC: TEdit
            Left = 60
            Top = 0
            Width = 121
            Height = 21
            Align = alRight
            TabOrder = 0
            OnChange = edPlaneCChange
            ExplicitLeft = 57
            ExplicitTop = -2
          end
          object edPlaneD: TEdit
            Left = 261
            Top = 0
            Width = 121
            Height = 21
            Align = alRight
            TabOrder = 1
            OnChange = edPlaneDChange
            ExplicitLeft = 264
            ExplicitTop = -2
          end
        end
      end
    end
    object tsPolygon: TTabSheet
      Caption = 'tsPolygon'
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paPolygonHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object imPolygon: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A000008F24944415478DAED
            5C796C1455187F6FB750114141E311AFC4708828828AEC6C2B01767666B58A17
            3512233112231A4F50F140011554BCF03EE211A33112825795EEECCE4255BABB
            2055046FE311834623A65244D876779EDF34DDF615A6DB3D66E6BDD7DDDF3FF3
            FAEBECBCEF7BBF79E7BCF761540157C0AC0DA8A0372A8270868A209CA1220867
            105E909A9A99C38C21A9EF21E96D4799D12DBABE93B54DA5407841245959016E
            DCDAE90C462BE2516D216B9B4A81D082D4CAF20919E4FD1A92D55D54CA8B3227
            6DD0F59F58DB562C84164492D53570B9681FFAED84AE5DCCDAB66221AC203E39
            340D23B2DEEA7F04A16052D774D6361603310559B2C4E3DF90D804057F7A1F77
            6C49D44AA7C37D066B530B85908240477E2598FE3245B5775D07F750646E428F
            BCC2DAD642219C20D3A64D3B2855556D0E738FA2DC788410826194B580BAF54F
            639067CCC6C6C636D6361702E104F107D46504A33B29EAAFEA746ACC9E21430C
            4F87610A7504E5DCB2B8AE2D626D7321104A90C98A726C9581BF85E481590EC4
            B92619D59E37D33E59B90623FC2CF593BDA40A8F4B86C3BFB0B63D5F0825080C
            7357C1E5128AFA1A6AC7A94D4D4D69F38FFAFA7AEFF6D69D9F835BA7500EAE82
            5A72296BDBF3853082F803218960D2DCDB661C4AE861ADD77D8A328318384673
            1E82A636C7B44F58FB900F4411044B413509138C3329EE0398009E677533D4A4
            0FE05247519FC13078B208C360210481029E0397D7282AEDC9A089CDEBB5AFAC
            EEAF991E1A6B78C936480EEA7614A339F1A8F63A6B5FFA03F7824852FD1034B4
            CDECC88FA3E895503B6ECEF9BB80BA12BCBBB18721BFEDF6A0B15B2391DDAC7D
            CA05EE05F1CBA1250491C514D59A21E9D19B62B1BF73FDAEB6AE6E442695FE01
            9287F6388B97C6F5F012D63EE502D7824833CE3D1A793ABE83E4D02C07E2DC90
            D4234FE5F37B1808DC000381277A18B2C78B8C1337E8FAAFAC7DEB0B5C0B02B5
            E30D10E0328AFAB6BD75C7849696968E7C7E0FB3FAAAD4A0EA2DA0E2F82C0733
            FA3792B1C8E5AC7DEB0BDC0AE2539429D8C009DA460FC675CDD1F0DA429EE397
            D53A0223328A22041B6725A3D166D63E5A8157413014E4C75090B51417838E5C
            2EE661304A0BC345CDFE0DB52E09CD9EBF33C919B814440A8666C37BFC264565
            10F24E4AE86BB715F33C9F2C8FC3C8BB159255DD8E13323B1E8BBCC5DAD77DC1
            9D205DC3DC6F20797C3749D0338998765D29CFF5C9CA3330CABA96F27C7BFB01
            83C7B63434FCC7DA671ADC09021DF9226852EEA3A87FDAD38347B73435EC28E5
            B992AA8E847A660E83476639C86711345DCB58FB4C832B41A6040247787095B9
            843E3CCB410FBC20190B3F66C7F3FD41750121E8118AFAD7838DB1CDD1E8EFAC
            7DCF822B41FC01F55582D11514F5E321833CE31B1B1B53763C7F7C7DFDE0835B
            DBB6414F3E26CB41FAD5A4AE5DC9DAF72CB8114492CF9E8490B119921ECAB80B
            E2BAF69EADF904940B10C6EF509401B5640AD492CDACCBA0CB673E2005D48FC0
            9AA9D9BFE1CD5D0F6FEE0C27F282A62B024D57902A857822AAD5220E86C15C08
            E20F28B308C6AB29CA20069A9C5CA77DE6447EB5AA7A6A26835A20E9A50A6216
            D4C635ACCB82B92066BB3EBCB5CD5C461F4599F562420F5FED64BE3E597D119C
            BF8AA27EAE4EA74E6A6A6ADACBB23C980B02CDC742683E1EA4A85DE9B477CCA7
            4D6BFF70345F45399C18D81CD11D9CE5C08E85C998B68265793015C4AA503046
            B7C7A3DA436EE42FC9CAED90E30314E5CACB900B4C0561DD6CB06A2E73819920
            35D3D5F186176D41F4FA12838ED562409131083E6D632CBC9545B9301384A7A1
            A79B43EEFEC04410BFAC9E0F4EBF4B514C2767569352A835E727A3E1F7DDB6C5
            7541785DBE707AD9265FB82E882F109A8F317994A2B858E0EB5AD83457838765
            3982C8FCA41E79DC4D3B5C15C46A091C237C775C0FDFEFA61D7DDA1750EF0683
            EEA5285B96FE0B81AB82F0FE91C8A98F6385C03541BA3EA37E81E8DD841C7E46
            B5FA7C8C3D64623C12F9D28DFC5D134492D546B884B27F73BCD1C0D60D160567
            EE462635C1D03906211F5214D75B71ACB62011839C935C1769743A6FC7051171
            B39A895237E9150BC705818EFC7AE8C89FEC61F8DFCE69C26A1B2BE07A68BA9E
            76325F470531373C1BA9F4F7D01E1FD69321FF1B9EB38061F05230F81E8ACA6B
            A37729705410E8C8CD49D54D3D8C184702B298A02843871A086A093E9AA2FB3D
            0A510A1C13042681A36012682E6D779F1D17E5D04C2F3FF63F2CD4E1C9E0539A
            D787BF73223FE70491D506B89C4B51C21C2BDB07FB1FA723B821110BCF742433
            271E2AFAC1CBFDFCB138708AB1A1C6A3D188DD79D92EC840389A6C85FE8E64DB
            05DB05F105D57998A0E7284AB8C3FB56B00A5A004DD73C68BA5EB0331F5B05A1
            C2ED1DD99D0141CBE331ED2E87CBCB154841653988700745FD657758415B0591
            E4D0C3F0DADC4251420680E90BD6816FC8C3093D729B5D79D8268845B83D246A
            88A45C9002A1B950ED5FA2A876031B276F8C467FB0E3F9B609220594B761E871
            21456D3966C4F03356AF5E9D71ABB05C8175F034DBC20ADA228855B83D91C3EC
            B1F4B774411C7E637885532D42C98238DDA6F20AA7FACC92047163D4C1339C18
            559624881BE3729EE1C4BCAB6841DC9AB9F20EBB57268A16C4ADB51DDE61F7DA
            5D5182B8B9FA2902EC5CDD2E461057BF0F8802BBBEFF142C88DB5FD044815D5F
            480B12A4D8707BE5023BC20A162608835D1822C18E5D36790BC26A9F92682875
            1F5ADE82B0DAC9271A4ADDA99997202CF7BA8A8852F632E72308D3DDE0A2A2D8
            DDFEFD0AC2FABC84A82836AC604E4178385124328A3931965310A7C2ED950B8A
            092BD8A7204E87DB2B17141A56B04F417839B72D3A0A3D976F29084F910D0602
            0A895C612D0847B13F060AF28DEDB29F206E87DB2B17E41B56B097203CC68F1A
            48C8273E582F415885DB2B17E4135610E7BAD9CD707BE582FEC20A760BC23ADC
            5EB9A0BF6EA153105EC2ED950B728515EC1484A7707BE582BEA616D8170CCDC4
            84EC1B5FDD5C50FC8DB5D1031CE6D9F77134614EBEB124AB66C8A409ACADABA0
            135B4D41CC8DC1C34A7E5405766097B9E9ED1E68C096B2B6A40264F6DD8B3B3B
            75F3AC4387C73382B53DE50C6FDAFB4F7C5DE38FCC83F157D01B154138434510
            CE501184335404E10CFF03AC720051F64686890000000049454E44AE426082}
        end
        object laPolygonTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 208
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Polygon editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paPolygonValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        object paPolygonV1: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 10
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 10
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laPolygonV1Caption: TLabel
            Left = 0
            Top = 0
            Width = 41
            Height = 13
            Align = alLeft
            Caption = 'Vertex 1'
            Layout = tlCenter
          end
          inline gvPolygonV1: TGeometricVectorFrame
            Left = 41
            Top = 0
            Width = 341
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 41
            ExplicitWidth = 341
            inherited paMain: TPanel
              Width = 341
              ExplicitWidth = 341
              inherited laX: TLabel
                Left = 33
                ExplicitLeft = 33
              end
              inherited laY: TLabel
                Left = 144
                ExplicitLeft = 144
              end
              inherited laZ: TLabel
                Left = 255
                ExplicitLeft = 255
              end
              inherited edX: TEdit
                Left = 44
                ExplicitLeft = 44
              end
              inherited edY: TEdit
                Left = 155
                ExplicitLeft = 155
              end
              inherited edZ: TEdit
                Left = 266
                ExplicitLeft = 266
              end
            end
          end
        end
        object paPolygonV2: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 36
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laPolygonV2Caption: TLabel
            Left = 0
            Top = 0
            Width = 41
            Height = 13
            Align = alLeft
            Caption = 'Vertex 2'
            Layout = tlCenter
          end
          inline gvPolygonV2: TGeometricVectorFrame
            Left = 41
            Top = 0
            Width = 341
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 41
            ExplicitWidth = 341
            inherited paMain: TPanel
              Width = 341
              ExplicitWidth = 341
              inherited laX: TLabel
                Left = 33
                ExplicitLeft = 33
              end
              inherited laY: TLabel
                Left = 144
                ExplicitLeft = 144
              end
              inherited laZ: TLabel
                Left = 255
                ExplicitLeft = 255
              end
              inherited edX: TEdit
                Left = 44
                ExplicitLeft = 44
              end
              inherited edY: TEdit
                Left = 155
                ExplicitLeft = 155
              end
              inherited edZ: TEdit
                Left = 266
                ExplicitLeft = 266
              end
            end
          end
        end
        object paPolygonV3: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 62
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 2
          object laPolygonV3Caption: TLabel
            Left = 0
            Top = 0
            Width = 41
            Height = 13
            Align = alLeft
            Caption = 'Vertex 3'
            Layout = tlCenter
          end
          inline gvPolygonV3: TGeometricVectorFrame
            Left = 41
            Top = 0
            Width = 341
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 41
            ExplicitWidth = 341
            inherited paMain: TPanel
              Width = 341
              ExplicitWidth = 341
              inherited laX: TLabel
                Left = 33
                ExplicitLeft = 33
              end
              inherited laY: TLabel
                Left = 144
                ExplicitLeft = 144
              end
              inherited laZ: TLabel
                Left = 255
                ExplicitLeft = 255
              end
              inherited edX: TEdit
                Left = 44
                ExplicitLeft = 44
              end
              inherited edY: TEdit
                Left = 155
                ExplicitLeft = 155
              end
              inherited edZ: TEdit
                Left = 266
                ExplicitLeft = 266
              end
            end
          end
        end
      end
    end
    object tsCircle: TTabSheet
      Caption = 'tsCircle'
      ImageIndex = 4
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paCircleHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object imCircle: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A00000F7B4944415478DAED
            5D0B785CC5753E6776256103B679B4E6691A92583204DAC4D8DA95642A6BDF06
            639AF0C80B4A8269090E4D290984E40B31315F80F42B4D48E00B1F9034B87960
            83D3E0DADABDBB2B2B45DA875DA7014A402689818F609B10CB16C8B6ACBD7372
            66F75EF94A5EBD56BB7BF5D8FFFBAE34AF9D3B33E7CECC999933E7204C722CF5
            784E7390A31604D411E04204A825A033F8FF8900821F3A05B2EE2C7A01B01B40
            F612BB91600F21EE42A05D20E1151DF5AEEDF1F89FECAED34840BB0B3014F5CD
            A1738453B670632E2784160E5A50E457BCCE796F6302B7915ED5966CFBEF3FD8
            5D672B2605415C5EEF2204E7F5FCB57F8CBD1F2C208B43C6FFD90534C02E427A
            8648AE4FC5622FDBDD16B6116471F3CAD36B1CFD9FE45E701D13E2921192EEE1
            E7373C4C7509125D9CBE0B847C3DC343524D55D57B1D5BB61CE07832EBD374D9
            65F3FAFAFB4F72AA614C8AF300A98E7B040F73B090E32FE0E7CC11DEB583DFB3
            BE3F53F3D39DED9BDFB1A35DCA4E9026AF774106C5EDDC4837F1EB67E549F247
            7EDAB9649D12A923AD69BF82630D5E8CF79F2F4178793E6AE26C7948C4B3F324
            EBE367034A714FA2ADF577E56C9FB211A4DEE7FB207FE15F6627F708A81A12DD
            CD5FF206F575A6A2D104149100A3D5BFDE1B6C14D932D135EC9F3724FE28976B
            3D08BC3F1989FCB62C052AF50B167BBD736BC0B98E1BFB16F63A86444790E8F1
            B9D58ECDADADAD7DE5A8F070686E6E3EE1A8A3FA7242C13D97FC43A233FC893C
            2CABC5DDE9D6D69E5296A3A40471F9FD2B91F011AECC399660C9CF56FEBB2ED9
            16D95ECAF7178AA640E0AF751D6E67E72761F047B4979F3B93B1C87A28512F2E
            09415CC1E05F41867EC0992FB7041373334F01C96F4C066E662C685C1EB8503A
            E06E765E332882B08DAAE0C65438FC5AB1DF597482347803ABF8D3F9013B4FB5
            04BF2A89D6A4E35AB4D8EF2B07DCBED0DF72C77E98FBC48596E01E405C9D8C86
            3716F35D4523482814AAE9CEE8DFE221EA564BBEBD88B0AE6FFF3B0FEEDCB9B3
            BF0C6D57325C78F5D5D5271FE8F92273875F8563EB1D9E1AE1A19E53E7DCF1D2
            C68D478BF19EA210645920706646C767ADEB0922785E82E39AEDF1ADBBCADF7C
            A583DBEFAFE3F96F0337DD45038108DB33FD8E553BDAB7EE9D68FE1326C852BF
            FF7D0E891118BCC25E7F7456F5CD3B376F3E5468BE93198A233B5255FD008F06
            FF6409DE2D5106D2D1E8AB13C97B420471B5043E8282392680F946502FB3B1AB
            1371ED6736B75959E0F2F83FC543F2639605EE3E00114AC65AFFAFD03C0B2648
            76A223C9C314CC3182F6F3177379221E4EDADD50E584CBE76B44129BD9798A11
            D48382562634ED7F0AC9AF2082D47B82170BA45FC2B195ED1E49184CC7C32FD8
            DD4076A0DE13BAC08132CCDCE5B946D0BB24A139D516F9D578F31A3741DC81C0
            0740870E38364C753940F777C4626FD8DD307642EDD131131335363115F6A214
            4DE3DD0B1B17411AFCFEBF24898A18C6044E7F40E96C4CB46D7DDDEE06990C30
            CE723A61E00C077F9FC988C6F1705F6326885A671CE8A70E0B6BBB5F9258968E
            B7FEC6EE86984C3056F7CFC1B13925DD73CA9C4BC7BA4E1933411ABCC1877815
            746BCE478709C9978A463BED6E80C90897DF5F8F12E33070B48CFF9E8C85FF65
            2CBF1D13415CDEE04711E869333D117D3C15D79EB2BBE293196E6F406D4CFED8
            F012215E998A869F1DED77A312444D563A38145F6DEE4D7D3F198B7CCEEE0A4F
            053478028F11C26AC3DB4D4EFCC8681B92A311045DDE40DCDCB555DB2127E87D
            AEF6F6F6237657762AC0EDBE7A169C78306DD96689F1C7EC1BE937231224B712
            C5FF34BCBD42C7C59DDBC25D7657742A21B7F7853BC1D8901C6DB81F9620F5A1
            D01CD12FD5B9C559B910BA2B19D3EEB7BB8253112EAFFFAB0878AFE1DD7B14F4
            BA9DB1D8C17C6987258895AB52A23273ABC4C5761FB34E55A8ADFB39DD3DCFB3
            B34EF911E1C14434727BBEB47909B2D4B362A10375B5BE50C79724083C9DF1C8
            36BB2B369551EFF1FB04A26678330ED06B3B62B1DF0F4D979720CCB23DC1FF3E
            ABDCBCDEF8592AAA7DC2EE0A4D073083F43437B812065407F28FA562917F189A
            E638822CF1FBCF754A54222FD5EA7728E8E284A6FDBFDD95990E509B9002E58B
            EC14FCF4732FF9C0D03DC0E308E2F604BEC7A16B949BA9F80C53F12ABB2B329D
            C0A3CF7FF1BF55590FC17792F1C83F5BE30711448977563BFBDE300E5C88245C
            52C8167205C3A3C1135CC2D38029FE7448A7CC02AB44FE2082307B762BB3670F
            19DE302F62427657603AA2C117D078919D5B20227C3E198D3C6CC60D2288DB1B
            DC61EEE672C4558958E419BB0B3F1DC10BEE6B79C16D1E73A7F9C37799710304
            C95D0970985BE9DDF3AAC49995754769A08424FA9C354AAA3F77E22A685152D3
            5E51CE018270EFB88F7BC7970D6F6503B1C4B06E3CF202FCDE544CFB9A725B08
            1250F253D9934042D95439EB282D1A3D816512C1148478853BC022E5C812C4DD
            72F9D920FADF3422DFE6C833A07C5702662AB0C11B789B1BF9F4AC4F569DA3AE
            D7E508E20D5CCFFF7E944D05F0144FE61FB7BBB433016E5F70232F2EB2EB3C22
            FA742AAEFD384B101ECF7EC8E3D90DD954843727E3E147ED2EEC4C00AF496EE1
            35498EE5457A2219D5569B3DE435FE779E724B940B272A0E59C1D8609C959857
            3376F354713EE656E747FF6804EEE1C0B3EC2EE84C027706252294937173C069
            6888427618F1A31E3156505CB8BC8136F3885C8070A3DBEBFF2C0F604F646309
            1E4EC6239FB7BB9033096E9FFFFB3C6FFFA372F3C47E0336F8020F10C11D2A00
            09BF9088871F9AD82B2A180F5C5EFF6D08F860D683741FF790C0CFD979652E1A
            83C9583862772167125C2DFE100ADC6A78372982A87BE16EE523D02F982A1732
            A70B0CD153E300103B1541D409D687B27E63B568772167120C41445358FD05B4
            AE418E823E6F38F1940A4A83A6CB2E3B45EFCBEC37BCBB1541D46955564CB426
            D357D5DEDE9EB1BB903309CDCDCDCE3E674DF68632B3BFEF2882A8330F25D070
            88D720274E2CFB0A0A012F3D0E19C7E67D15824C020C254865C8B211F986ACD7
            A032A9DB867C93FA00DB2B33E2DC747BEB9B85675FC178918FED1D58184A1217
            56EE0C9617F91686C7B64E0842C978246C772167121A7DC11592688BE1DDA46E
            48DDCF93C99DCA57D95C2C3FAC9B8B48F04D75D0FE1943BF951247792415D3D6
            D85DC89904EBF63BE3EFD1DDE26F0081A6C84F9CD7225EBB0B3993C05386BA77
            D3ACDC24C8855955DEE83475D4568E70CB0CEB11AEA3C679EA71420E3A396AA7
            9BD2B1C98ABC420ECA551103B2076E5F600D4FDCDF536E9ED01F4FC423375504
            E56C84F58A1BE353DC437E922548A3CF77162F0ACD83A98A286939B076AD68E8
            48EE33454905CAB33BA3D1B70684AD99FDED32753D49C065E958B8A3D0775530
            3A1AFCFE4B49E22F0DEFCBDC0994A1008BF4BBCFFF4D9E3FEECA7A901E4D46B5
            9BED2EF47406B7F7E3DCDE37663D08EB92D1C8DD39A701E36EBAA936E320F4CE
            393399DC78D8EE824F470CBDB02374AC3355960CB9D21650971197642388AE4E
            C4B5A7ED2EFC7484F54A1B01A55231CD6DC60D2588925AFCAEE18DF0B816B4BB
            F0D311DCCE4AE57A76470409D724E2E147CCB891AE45831474495AD376DA5D81
            E904774B602908481BDE91AF452B0C56E5079BB8977C6C2C2FAA606C606EF617
            CCCD5E6178BFCDED7B9B35FE3882189A35956AD38A6A8D22C3B04BA2B4F3A976
            EF0359F5FEA18289F995CF585932800D4CC56BEDAECC7480DBE3DF04887F97F5
            0CB3B4C84F909CB264B5E9E5CCA5426F321A8EDB5DA1A90CB73718E001C73C8D
            EDD705D56ED7B4DD43D30DABC0CCED097C9B63BF60785F9D57252EAA2812280C
            860233A586BD361742FF9A8C6977E44B3B2C411A1BAF3859CE3AF2F2805939C2
            AF24E3E1FBECAEDC5484DB17B89B171CF7643D086FD6F4F72D6A6F6F7F2F5F5A
            1C39A3E02780E82786F710085A6CAA80A8606CC8E9C8D2FF77C0A405E2352399
            491A556FAFDB138CF304D492F3D18BD03BB7BEB2A532362C5EB97276F591A3DB
            4DDB5588104D4423FE917E332A410C0D738A553B4DF987534D57C1F1707903CA
            52DD670C6F51142967C1ECDA954CDE4D96F4D9C314BB2B3C99D1E00B5C47044F
            1A5E2241AB529AB679B4DF8D5919FF60AE8B0E4B10FECA99497E347A432E0932
            0686327E26CCBFA5E2912F8EE5B763264896753BD0F31C8F594B8DA0FD42874B
            3BB7455EB2BB0126131AFCFE0F9144A5E5276BAE42EDE6F677FFE9D2B19A0D1C
            97419765A1D05FE8FDB2C36245E62D1E171B4B61F1722A426D3B399C3261317D
            F43B4999C6743CBE6FAC798CDBE451434BE8FD24B25664E61B19EC02E9F0CF74
            2B3B0D2D2BCE23A1AB6D75D37CE05E07E88DF994258F84828C82B9BD2B2E02D0
            55B71C300AE67040A8231279DEEE86B103798C82F50088E642CCE7156C36CF38
            A4575C836936AF9B50AE9C699AE8EABDC12601A40CB598268E0E0A82959DF1C8
            7385E43721C3926E6FE8C300B215062CB6D161E6286E528AB8EC6EA87220C7DA
            D2A316C3927B116528118DFEBAD03C4B667AB557D0E75ED0B45E9BDBAC2498B4
            A6574D2C695E7186B34AFF85852506B5CD4220AF9D6EAA3AB27B53426EB09AF2
            56ACAD10B02AA1696F4F34FFA299EF56B7498F386BEEE50CEF38962F1D4610DF
            9A5B85F74DF5ADFBC58B1757559F7AFA2DDCFACA30CB49463011D277DF9D37F7
            4B93CA7CB7152E5FF00A24FA210C3670FF5BAEC8AD53F5BA5CA327B05C2228DD
            888B2CC1070D43CC4515952A3A41140C9E5C2945F30C7E1B3E0D24BE918C6D7D
            B114EF2D36B267E019FAFAC0B1EB4035202A485F5D0A73B32521880997DFBF12
            252A71FB05966025C4BD8504DD9BD2B474815997140D3EDFDF1089AFB0F3AA21
            6DF4163F77256391270BCB79749494200AEAE49166F7AD6576587124CE412FE7
            2F4D123C7E42A6EF59BB4DF165392747F52A21F0C601CB05C7D0CFA5FD4E4DE6
            C83DC39DF4150B2527888926AFF77C1D9C777207B90172224656F0780C1BB930
            4F762E7377C2DAB5B22C8552570212892626C0F540A87AC3DC2129FA00E93F74
            8407F209249402652388897A8F673EA2F3367EB112C69B9D27C9BBFCA4B9F7C4
            74A4585AD3944199A2DD55511F8604E1254025CAA94E424FCB938C3942FC91CC
            E0BA726BB6283B414C18974D95B1B14FF3533F42D27DFCF5BEC45FEA2EE6F777
            8184571C846F103ADE13B3B0A763C99283033D8ABFF8A61D3BE6CAC33407493F
            8909BA0004D431716B993F5DC895557730E60FF722B59EC81AD214F0D36424B2
            1F6C806D04B1A27179B0961C741DE5AE77D51590C521E3FFEC027EFB3213E219
            49CEF593E1B2EBA4208815EA7A9D2E71397FA96A38510A86DF57E457ECE6DED6
            4612B65539B1EDB948648FDD75B662D211642894FA22EA93B53CFCD4F1C45FCB
            03CB422EF67C223A89897632FBD51180B972660E080F70DCBB1CC76EDAC78DDF
            C58DDFE5404717D688AE8E2D5BBAEDAED348F833C81D4585313AE81D00000000
            49454E44AE426082}
        end
        object laCircleTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 174
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Circle editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paCircleValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        object paCircleCenter: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 20
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 20
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laCircleCenterCaption: TLabel
            Left = 0
            Top = 0
            Width = 33
            Height = 13
            Align = alLeft
            Caption = 'Center'
            Layout = tlCenter
          end
          inline gvCircleCenter: TGeometricVectorFrame
            Left = 33
            Top = 0
            Width = 349
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 33
            ExplicitWidth = 349
            inherited paMain: TPanel
              Width = 349
              ExplicitWidth = 349
              inherited laX: TLabel
                Left = 41
                ExplicitLeft = 41
              end
              inherited laY: TLabel
                Left = 152
                ExplicitLeft = 152
              end
              inherited laZ: TLabel
                Left = 263
                ExplicitLeft = 263
              end
              inherited edX: TEdit
                Left = 52
                ExplicitLeft = 52
              end
              inherited edY: TEdit
                Left = 163
                ExplicitLeft = 163
              end
              inherited edZ: TEdit
                Left = 274
                ExplicitLeft = 274
              end
            end
          end
        end
        object paCircleRadius: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 46
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laCircleRadiusCaption: TLabel
            Left = 0
            Top = 0
            Width = 32
            Height = 13
            Align = alLeft
            Caption = 'Radius'
            Layout = tlCenter
          end
          object edCircleRadius: TEdit
            Left = 196
            Top = 0
            Width = 186
            Height = 21
            Align = alRight
            AutoSize = False
            TabOrder = 0
            OnChange = edCircleRadiusChange
          end
        end
      end
    end
    object tsRect: TTabSheet
      Caption = 'tsRect'
      ImageIndex = 5
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paRectHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object imRect: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A000002CD4944415478DAED
            D6CD4E136114C6F173DA1A5D08E207700384E85613A5DDB6D3E942D00BD07003
            7A0BA0D7A03780716D4C80C496B233141358FB11BD006AD2A6C1AD733C433A32
            695CAAEF93CEF35BB4EF7B6648DEF49F2955C9B95BAF5FAFE885A72276DF4496
            7D3423F42F9C8AE867936447CBFAA2D76E0FB20B9A2D56A2D69A9A6DF9722EF4
            690B6668255B3FEC74B6D3CD59905A237EE04FC41B5F96429FAEA0128FF2308D
            A2E9D754592BDF7C7865E2A6BEF7FA11FAA4D3C92EFBCBC2C470286559D25AA3
            F5CCC43673174EFC697974D86D77431F7B9ADDAB37A392EA6BC98751D9D46A23
            3EF6E5ED6CE63122C6F83F6A51D4342BB5B3BDFFFF384E838C7C3D3B9EF57BDD
            F662E8831648FAF99FF8FBFC783F4A0796BBE19307B915FA9445E29FFF477FBB
            99ED1924300601C3206018040C83806110300C028641C03008180601C3206018
            040C83806110300C028641C03008180601C3206018040C83806110300C028641
            C03008180601C3206018040C83806110300C028641C03008180601C320601804
            0C83806110300C028641C03008180601C3206018040C83806110300C028641C0
            3008180601C3206018040C83806110300C028641C03008180601C3206018040C
            83806110300C028641C03008180601C3206018040C83806110300C028641C030
            08180601C3206018040C83806110300C028641C03008180601C3206018040C83
            80F9539091BFCF8EF77D0FB218FA9005A2B546DCF727E2C6783F4A07473EB893
            DD9198353FEC77F6429FB408AA8D562C62EFCE277AA4D528DE1093E7B9FBFAAA
            C9E383BDBD4EE8034FB3718C57BE5CF83D34D9D06A1C5F939FF2D5B75727FEE6
            BB173B0D7DF0E96433FE323F311C942F5696345DAD349BAB9AE85B5F96421FB5
            A0120FB176D06DEF6A3659895A6B6AB6E5CBB9D0A72B988198ADF7F63B3BE946
            F357CEBEBE127922A6ABFE582DCBF9AF2FFABBD25FB65FFC7FC676F952E5E5FB
            DDDD6176E117E49DCDCD95951C9D0000000049454E44AE426082}
        end
        object laRectTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 235
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Rectangle editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paRectValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        object paRectLeftTop: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 20
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 20
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laRectLeftCaption: TLabel
            AlignWithMargins = True
            Left = 5
            Top = 0
            Width = 50
            Height = 21
            Margins.Left = 5
            Margins.Top = 0
            Margins.Right = 5
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'Left'
            Layout = tlCenter
            ExplicitLeft = 2
          end
          object laRectTopCaption: TLabel
            AlignWithMargins = True
            Left = 206
            Top = 0
            Width = 50
            Height = 21
            Margins.Left = 25
            Margins.Top = 0
            Margins.Right = 5
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'Top'
            Layout = tlCenter
            ExplicitLeft = 208
          end
          object edRectTop: TEdit
            Left = 261
            Top = 0
            Width = 121
            Height = 21
            Align = alRight
            TabOrder = 1
            OnChange = edRectTopChange
          end
          object edRectLeft: TEdit
            Left = 60
            Top = 0
            Width = 121
            Height = 21
            Align = alRight
            TabOrder = 0
            OnChange = edRectLeftChange
          end
        end
        object paRectRightBottom: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 46
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laRectRightCaption: TLabel
            AlignWithMargins = True
            Left = 5
            Top = 0
            Width = 50
            Height = 21
            Margins.Left = 5
            Margins.Top = 0
            Margins.Right = 5
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'Right'
            Layout = tlCenter
            ExplicitLeft = 2
            ExplicitTop = -2
          end
          object laRectBottomCaption: TLabel
            AlignWithMargins = True
            Left = 206
            Top = 0
            Width = 50
            Height = 21
            Margins.Left = 25
            Margins.Top = 0
            Margins.Right = 5
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'Bottom'
            Layout = tlCenter
            ExplicitLeft = 203
            ExplicitTop = -5
          end
          object edRectRight: TEdit
            Left = 60
            Top = 0
            Width = 121
            Height = 21
            Align = alRight
            TabOrder = 0
            OnChange = edRectRightChange
          end
          object edRectBottom: TEdit
            Left = 261
            Top = 0
            Width = 121
            Height = 21
            Align = alRight
            TabOrder = 1
            OnChange = edRectBottomChange
          end
        end
      end
    end
    object tsSphere: TTabSheet
      Caption = 'tsSphere'
      ImageIndex = 7
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paSphereHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        ExplicitLeft = 10
        ExplicitTop = 13
        object imSphere: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A000012454944415478DAED
            5D0D7854D599FEBE3393445008A02E228AADB52460756B113293041A32FF20E2
            B6A2D56A6B15BB56745D6B576BFB54517844DD675DC5E2531FB53FD256056157
            29647E43BA24331358BA2BD69FC4B6A86B05D4128806F233F79EFDCE9D7B939B
            61FE3299C94DC2BCCF7367CEB9E7DE73EEF9BEF3F37DE77CE71C84518E0536DB
            E9266EAA0006951C7036025470E067D1FFA9008C2E3E1514B7822E00EC0090BB
            38B991C3018ED88EC0DB4186B72594DA7687427F333A4FE980467F4022AAEA3C
            E730B35C4FC45CCC11EAE9D6AC3C27F11EC5BD9318DCC8A592C648E3EFFE6A74
            9EF518150CB1D8ED7310CCDFA2D2FE75F27E3187288EA9FF137320403B47BE85
            73796334187CCB685A18C6907975CBCE2833F55D4BB5E07A62C4A5691E3D40D7
            9BD44CB531CEDAE8F93660F27B316A92CA4A4A3E6BDEBEFD0885732D3FB54B97
            4EE9E9EB3BCD2C9A31999D07C82BA946503307B3297C2E5D33D2A4B587D2D9D8
            172B7B616FD3B64F8CA0CB8833A4D66E9F1543761711E9664A7E4292473EA6AB
            89BEAC4546DEDCEAF7FF0106089E8FF4CF9781D9A93FAAA568A949C499491EEB
            A16B13CAEC817063C39F47923E23C6902A87E38B54C27F484EAA11509210DC41
            257993289DD140200C796440A6FC57D9DD354CF9267E15F9A72484F7D2776D04
            860F477CBE3F8DC807153A8179767B791998D710B16F25AF2921D8879C3F5B5E
            6ADAD6D0D0D03312194E85BABABA537A4DA59771645473B9332138464564835C
            CAEE6B6D68E82CE47714942116A77319727C8A32738EEEB64CD70EFA5D1369F4
            ED2E64FAB9A2D6E5FA7B4982BBC8792D0C2E4407E9BA2712F46D8402D5E28230
            C4E2767F0E62FCE714F962DD6D4ED2CC4BC0E507478334930D6A16BB2E944D70
            1F39AF1A14C0B19197C04D51AFF7DD7CA799778654DB5DCBA9E8FC9C9CD374B7
            DF91395FD51AF207869DC0EAD5CC128DCE627D702675FAE588380965B94C42F6
            416BD0DB9CEFFC08581D9EAF52C5DE4075E242DDED4E405C19097837E733ADBC
            31C4E3F19475C4A447A989BA5D176F1722ACE939FCC9637BF7EEED1B6A9CD4AE
            9BFBCC132E25662EA6CEF512CE6136C5574141A724CD0CCAAE7020E0CF278134
            5CB86245E9A4239D3F20E9F0C730A0EF50D708EB3BA74DBEFB8DCD9B7BF3914E
            5E18B2D0E59A1193F055BD3E41C47B4D06D355BB433BDA87121731614AAFB96C
            05D5B2E5E45D44D7A4EC73835FA312FB1FF9C8532A589DCE4AEAFF36516217E9
            A8B83BD6675ABEA769C7C1E1C63F6C862C703A3F6F92D1078335EC8DBD134A6F
            D9BB6DDBB1AC22A166A8BA39E2212690B60E97438A1AA0E23015CB7604FCBFF8
            B8153F86620C8BF33F8643FE17879B9F6C2024B2EE92D247A835F827DDEDFD32
            D5D0D640E09DE1C43D2C8658EA5D5F41461213C074F5561789B12BB3258C6892
            7A4BCAAEA1DA24F493B9491EE9A60E344CCDD44E8EB8CB6C86377735347C9C47
            DA0E0B169BF39BF46DCFE814DC4300CC130936FC4FAE71E6CC10A5A3E3323553
            3059BD75984ACC65E19037924DBA56BB8B9431BC9F4AF8F90961DDF451AFD0FF
            C6D2584FA8A9A9A9BB90441D2E2C0E470D72B68D9C53D55B9DC8F8B2B0DFFF5F
            B9C4971343AA6CEE8B19F2DFC380667B40E6E86E0D79F7657AB7DAE9FC129770
            03A5BC28E143DA492E7EAC17632FEE0D068F8E1C49878F2A9B67AE09652F35B9
            E7AAB73EE532D4451B7D7F186A5C436688D5E5BA002410E2A5D64CB599407236
            0783EFA77B4F91523A3A1FA404BF0F83874EF65133B76EE6B4F2CD04C9209A0E
            1B628C8E8498803A8829701065563BD4B1B02131844AF7DF71190533D40E9CFF
            1565734DB871C77B993E5642D30B242256EB6E1FA6D41F8CD4589FA44E5D369A
            A0F9803A97D302FD7338F897588CD50C45FACA9A2142CF38D2C79B75A2ED6199
            B385ADA18637D3BD67B539AF207154288A5A1B4B85089F0113BF37E2F31D369A
            88F986AADDEFD2E5B7B573EAE445D9EA295933A4DAEE5E4FE2E6ED711F3FCE91
            3BA281404BBA77A8E3BE8DFE9EA08BA9897D429AF5B75B02DE1D4613AE90B038
            9D55286308FAA796F1DF2341EFF7B379372B8658ECEEAF21F097B5E739E7DF88
            86FC2FA58B9718783F31F07E5D4ABBB909AF2EC4F8CF680415463130F91BD54B
            F20A5E110D785FCDF45E468628ED3F98845CAD8D4DFD2C12F47D2F5D9CF4314F
            D1FF2DFD3738FCB254EAB99944D898D1841A4954DB5CCF708495AAB7839BF12B
            990A642686A0C5EE0A69A3B66238E414A9C7924E37B03A9C0F913277AFE6A7A6
            6D7DB4A6FACEF1D2710F0556EB8A0970EAD156DD304B900AB323DD3B691912D7
            44F1D7AAB78B4938AF65A7B72DE507385C775097FDF8C01DEAB883FE878D268C
            91888F7DE15E5007243335F7291952E5F14C667DB298B7383B7E273D7155696A
            0B681D38C2A3E180EF1EA309321A60B13B7F8C806B55EFC15E902A5329BF2919
            A297AA84165D5EC22E4E35CD9AD8CF5029F83595023150385273E3A31A42299E
            DCD1F91A392B859F0AEB635458EF4AF66C52862CB02D996D4249E81762FA9233
            0EB696906F67CAC48E74EE22D22F506FED2A8BF5D49F6C1D782654D99C0E86A8
            CDD5C44C20553407837F497C2E2943484A7A8EFE6E146EEA945F8C06FCD7A44A
            883AFD8729927BD4C83E9162EC92D6A6860F8C26C06804D1EA65A2913006144D
            C733D1A0EFBB89CF9CC090F94EE7B9661985C94BA9780F19BF38ECF7FF315902
            AA562A9A2A313695B5AC7DB2420C4232945F87783FDB47B5E482C431C0131862
            B5B97E4A7757093771710B71F1CA14F10B7DA391FEEBE23EFE7424E0BF058A48
            0BA2D97F427C365410F88948C8F7CFFAF0410C11E69DA5E69EF7D50917CE65B8
            34D51072B5C3753DE925CFABDE8FA9B7A91C8F6353F946B5CD3D9FBA01CDFCE9
            98C463B3F416F9831842E2D9ED249EAD57BD5E52623CC9225DB16285E9838ECE
            B7C979811AC98DE1A0EF17466776AC800AB39F0A735C4144B82D12F06DD0C206
            31C46A77EFD1467329E04A22F296E411BAAF23D176A3EADD478CFB321445DCAC
            410AF7D5A4706BD3DCAD443F8B16D6CF90F89200933694DE31A584CD48A17788
            BE43CC0C7E4978B218682C2201C248A2C75C26ACFAE333AE8CCF89F8FDA2C519
            6008D58E7544DE1FAADE940388D576D752AA0ABF535F6E9F3975F2DCB13CD367
            14F4038FA480AF8D06FD3F116E1D435CC27E4A9909E428D7A69AEBA0E7446D88
            9B5672BC2512F23E6D74E6C6226A6CAE8532826608F136558039C2A130C45A7F
            D94C607D9A32F711059E0549FA0461C95E0AEC802A857593463E8334F2234667
            6E8C02A9B5F988887C86E2934BCE11CBEBE20CB1BBC4B8D3AF94A7005EA2CEFC
            1BC962A8B63BBFCB019FCEF45C11D9C1EA706FA64E58D1F3A82FBE8EFAE2DF28
            0CA1F6EC17D49EDDA03C95A61922C689BE63A970D38B971143B61B9DA9B10CD2
            496E259D242EF2227F8E14EB955A0D7997FECE136E19E5D9C9CC218595214906
            4281118671DDD035795A24B2F9B8D1991ACB50E74AB4A519FBA9AB381FE3DA79
            AF669E79806E9E9DECE51ABBC72283AC592586E839BBD1191A0FA0CA204C84E2
            366E26381D5553486D5D45CA2946ABCD7D2F55AB87849BB4F99F8483DEB559A5
            58445A58ECAE466D8A9C01B39292E7BC9148FC9C12CA614324E4BB2DD98BC4C9
            4DF4B742B891F1AFE66ABB5AC460581DCE9F51BFFD8FC24D1DFB0D58ED703DC2
            39DC2D6E20C73BC221EFFAA42FDA5D62C6EB62E1EE8D959E69D43AEEF1068BDD
            7927B5388F291EE4EBC4308858E072453C18DD91A0D777C25BAB57336B73F833
            55FF384CCDDAE9466764BCC052EFF42043CD7070AB608858176E153E0ED2DC64
            0B32C5224E8CF1FDAA37420CA9CE32BD2232409DE4532700B1453044CC602903
            859AB698F8926A1A19555E292A8479856A20A219ABEF43BD0ED20BD29464E629
            2409D88911CA0A5AE4F06C38E4BBD9E88C8C17D42E5D3A55EA8969137BFB0543
            84B2A798EF94C57A4A92598BA83657EA62CAEC0D878BC80C55E15656282BC6E8
            C41031E7210C1A8E51DF706AB297064DD722AC89047CF7199D91F104523D8EA9
            02534F560C51D71336291EC46B2301EF0B4667623C219121199B2C0161E86542
            9C481DFA2B4667603C215993F52E64E8D48B281C9275EAFD62AF1C63E716AD0E
            4716C9C4DE7EC550E6ECC24C6B068BC82F9229860343271C3C9190CF6BF4479E
            4CA871B897C89C6B137D5B7190B1749AC1C5220A03FDE02229DD0F8989F6EFA8
            FB5B097394A7A241FF2AA33FF264827EF89DF06DB4D63BAB81A166F2539C091C
            61509721D6DDD4093767DC82CA56DE68D6E636524EE1165118E8A7704D65E669
            27183948DC5431D44DC78AC80D498D1C842B5B33A022F20BABC3B58A3AEE9F0A
            B7368A3E2443B922F20BFD1237C237A986FC5661488DC371362985DAC4544A53
            D222F288F8B6868734535286F2CC9640E0C37E636B127FDBB4BD9E64C08585DA
            72B58838AA9DCE455CC6DFABDEB7A812285B1C0E58BFEBB7C428AE172C3888DE
            CF12BD6F523CBA39A67E86A86BD3B56D338E42D7E4194553D1C22071C10E93B0
            52DBB22461499B4B2C469CAF0470BE221CF2BF6CF4C78F47E897B471E0D168D0
            6FD5C2121922AC169F54BD3E6AD7DC467FFC7804D159188C282322C8715538E4
            7D4A0B4BB72C1A64C62F6DF5FBF71A9D81F1046BBD6B01306855BDE997450B0C
            DECA0FB6522DF97A360915911D489A7D85C777EF16789CE87BA73EFC0486A83B
            6B8AAD4D336EAD51C4D0A09E4B22B6221174EF01B9E40B898689C9379FD18B64
            009B888B571B9D99F100ABCDB91510FF41F1A4502D923324BE59B218F432C79F
            427B24E00D199DA1B10CABDDEDA206479B8DED9318AFD8EDF7EF4F7C2EE50666
            569BEB710ABD43F5BE33A5845D64F439516315EA066662B3858AF81DFEAF91A0
            FFEE64CFA664484DCDE593E409DD6FF51F2BC7F1479190779DD1991B8BB03A5C
            F791C2F180E241F8A0ACAF674E5353D367C99EC5F411B9AF01CE7FAB7A8F01E3
            F3B42D208AC80EF13DB2A4FFEE3FD202F1AA74C72465DCB7D76A7387A803AA8F
            FBF8EBD0555E551C52C90EF3962D9B58DADDBB5B3BBB0A1102E180CF99EE9D8C
            0C51779813A29AB26A2AD5D674459C088BDD254EAAFB8EEACDCB46CA0AD4E508
            5B75CF2B93294667783423618337CE195F1EF5FBB7657A2FEBCDF8074B5DFCB8
            0CCC599C33490E754D7F10D4CDF88931FF160DF97E90CDBB593324C976B08799
            048B5A76FADE309A00A309CA0942328A25E3CA71156234B7AFE36F8BB23D3670
            4807BA2CF478CE94FAE466DD29321F52BB5873B29C78900962D8C96496C3BAA3
            8FFE2CF3584D6B287428DB38867CE45175BDE70B9C29A7C84C57236807D9E4CC
            74CACE784775FD92F33893C4B0BA767CE041134835C9364B4E879C0E05B3DA97
            5C0420896AD97F2898C9049E669FEF35A3096304921C0AD609C0EA72393E2FE7
            63F3D4497A213568C7E675709497653A7567BCA1CAEEAE65C0C5E6D1DA114747
            1987652D21DFAE5CE21BD6C19256BBE71200B901FA4F6CE3C749A2B8596CC465
            34A1460271D1963FAD3B58F220A2EC090702FF9B6B9C053B7AB58BF1EFEDF3FB
            BB0CA65941306A8F5ED530BF6EC959E612E9159D480C629885837CF558393B3D
            5B2863534CDEA43FCA5B88B68CC1F2B0DFFFD170E3CFDBF1DD623569B7B96C2D
            4578F740BCFC38027BB4BC04D78DF5A1FB79F3E695944E3BE356A2BED827EC34
            F536E7C89FFC744AF9BF8CAAE3BBF5B038DC9723E762DB71FD01F77FA28CDC3E
            5697CBD5D85C8B6504B137E21CDDEDA3EA41CC793595CA3B430454995C6C8A66
            1B9C1ABE0C9C3D1809EE78BD10E9E61BCA1C788CDFDF3FEDDA9F0D08302EADCC
            74DC6C2E28084334589CCE6528A330B79FA5BB2D8CB8B773C6D746FDFED61CA3
            2E28AA1D8E2F73CE7E44CE2B1368F4215DF74682BEE7738B39330ACA100131F3
            C827F6AC2671584824E64189534993393C7B4AACE755A38FE956242753E972C6
            F0A6FE930B06D0475FFB4459ACFB8154337DF942C119A2A1D66E3F5F02F33D54
            416E80B889911ED41EC366FA98E75B165A5B46ECCC43B124201CAE25067C0B38
            8ADA509EF0440F20FFA584F0483283844260C418A2A1CA669B8E68BE931216C6
            7813933CF2295DAD547B8212F260ABDF2F0E94C9DB5A1551306460760E284C39
            C54C68B2ED0A4922C45FC9315C33D23B5B8C384334A88B4DC56163D7D15595E6
            D143547ADFA092DA4EF27E3BC8F0B689E3FB1C4D9FB109D8D93C7FFED1FE1A45
            25BE76CF9E72F9389F8C5C3A8D183A0B185412732B483E9D4D99156B30A6A74A
            48E813CA419A0C5E30EAB420C318A247CD62770537F1EB797C7957650E511C53
            FF27E6F0EE5BC4882D32376F1C0D8B5D470543F410CBEB241917534915CD89D8
            60F8F3794E623FD5B6462EC3CE123336EEF2F90E189D673D461D431221B62FE2
            3D7205353F95D4F15750C3329B3E7B3AE7FC3462DA24F28B29004D73165BD91E
            A1B04F298CDCFC1011BF8D88DF6642531B96B1B6E6EDDB3B8CCE533AFC3F1687
            A7947F913EC30000000049454E44AE426082}
        end
        object laSphereTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 194
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Sphere editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paSphereValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        ExplicitLeft = 10
        ExplicitTop = 115
        object paSphereCenter: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 20
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 20
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laSphereCenterCaption: TLabel
            Left = 0
            Top = 0
            Width = 33
            Height = 13
            Align = alLeft
            Caption = 'Center'
            Layout = tlCenter
          end
          inline gvSphereCenter: TGeometricVectorFrame
            Left = 33
            Top = 0
            Width = 349
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 33
            ExplicitWidth = 349
            inherited paMain: TPanel
              Width = 349
              ExplicitWidth = 349
              inherited laX: TLabel
                Left = 41
                ExplicitLeft = 41
              end
              inherited laY: TLabel
                Left = 152
                ExplicitLeft = 152
              end
              inherited laZ: TLabel
                Left = 263
                ExplicitLeft = 263
              end
              inherited edX: TEdit
                Left = 52
                ExplicitLeft = 52
              end
              inherited edY: TEdit
                Left = 163
                ExplicitLeft = 163
              end
              inherited edZ: TEdit
                Left = 274
                ExplicitLeft = 274
              end
            end
          end
        end
        object paSphereRadius: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 46
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laSphereRadiusCaption: TLabel
            Left = 0
            Top = 0
            Width = 32
            Height = 13
            Align = alLeft
            Caption = 'Radius'
            Layout = tlCenter
          end
          object edSphereRadius: TEdit
            Left = 85
            Top = 0
            Width = 297
            Height = 21
            Align = alRight
            AutoSize = False
            TabOrder = 0
            OnChange = edSphereRadiusChange
          end
        end
      end
    end
    object tsBox: TTabSheet
      Caption = 'tsBox'
      ImageIndex = 8
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paBoxHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        ExplicitLeft = 10
        ExplicitTop = 13
        object imBox: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A00000A1B4944415478DAED
            9DF9739BC519C777F795653BE0386969293494402F0A3D063289EDB899717CC6
            01D3D2C6243497434AEBDE9D4EFF00FF01FDA16428711CDB103B178869212E91
            2DCBC133712C9B8CE81DA6E5E801253034603B24B664E9DD3E2B59D6A358D6F9
            1EABCC7E329BD1AB7DF5BEBBFB7D77F5ECB3F23E941428158D8DEBB4306DE794
            3C02873740BA48083DA2D370EFE4F0F06B76972F57A8DD05C886752D2D2B9CB3
            811D50EC76385CBFCC691CFE9D859AF5044B9DCFF90706AEDA5DEE6C2808412A
            EBEBBF44286BA79CEE81C355280B7A02EF62948F8639DB069511F9B7A0FC6948
            27E073BDE32383E7EDAE4726482BC83DADADCE955397BF4138FF1E1CD6A1B2EA
            90CE70C60F4C783CBF27A2472CD0DADAAABDF5E1CC6638517CE69B908AD0255F
            A5941CD11CACF7ACDBFDBEDDF55B0EE904A9AA7DE0D3549BDF05ADFC6368EA35
            28EB22BCD7E720E127C7BCDEFFA4BBCEFA9AAD9F721485B7C335BE0B875F4659
            0148A740D0FEDBCACB4FBB5CAEB0DD75C6C821484707AB1CF3D52E3CD90F4172
            2CE4447A03A1B4AB787EEE77A3A3A3A15C2E2F0C00A633B836FF0E1CDE18CFE1
            FFE5841ED5193FF4B2C7F34FBB9B4160AB20157575376BCCD1C675D20E25598B
            B2A638E57D2CAC1D183FE37EC3B0FB3537AF64F3BA18CA7643AA475951E109E9
            275756BA7C3ED7AC5D6D628B20D12796FE0C5E82C5141FE7A1307EF125CDAF94
            F79BDD28114381687BE19E8FC2E12750D61494E4594AC307C78787FF6875DB58
            26C8BAFAFAF262C2B6C310F1139238A6CF40314E6A1A7F726C68E84F56370032
            1E8485D60C49438DE387794E3F61A4DF3734F48115E5315D10347EEF24D1095C
            8C5728E1879CA1E071F86EF8C88ACAA663D1A0E0E4FB707807CA9A8334004645
            D78477688420CBCE684C11A4A6A6A624E0287E185EFE1CD2BD282B6AE1442BE6
            35AB5279133732A0D7F06DD04CA5A8C1FE01FF9F6024D49B89B5972D860A52D5
            D87817D7691B5CF43138FC58422528E90DE9A1EE9747462E99DA9806030FD7AA
            A0C3F9308F7A07F0C325CCE597840518FCE0FDE7FD7EFFBC11F7CB5B901413B8
            20A417ACE8E65621865FCAC91E98F9EF22E88103DE05ABF05946C9E1718FE7AF
            F9DC23674136D6367F5667FA6349AC9477A0E5FB79883D3139EA7EDBDE263487
            C8905C54D292E4215CB4143F62E4D89F3D9E2BD95E3B3B41122770DF22718BC4
            90095C2152D1D0F0798D6B3B39E1FBE0F033282B623D42C3F44F7A07C732BD5E
            46826C6A6ABA25AC933D607DFC000E6F4759EF416F785AA699AE5D18E5474B25
            08ADAC6FAA4B7683887D4EC88199D52B4FFECDE50ADADD18B2918F1F6D8920C8
            AA1033E9BB51D6349CFE0C21EC099FF7F45FECAE74A190AD1F8D26F9A0B02056
            A013F2FA925244C9D48F46ABEA9BC4E4E797D0F45F41275D8121E9389CDA3971
            66E815BB2B73BD5151B7E5AB8CF26E72CDAA2725FCA210E43234FE8DD78C5D17
            201DD48A1DC7C65E7CF143BB2B70BDF0F5FBEF5F1D0E84F6C24BE19AB92BF63E
            B47D882F2C39084178F44DFE268C69A2FB7C0E5D03BB3AAE8BC99D1DA4F0E75D
            8086EF82C9E6B7A161378937160501467DDEA1CDCB7E9892B7C1EC3D461CB473
            6270F05F76575276903F4F1847F7A1AC25FE3CD0E025F111F17A8920B14FC5DD
            E54C7CC754A30B2E4E02675695BDA0CCDE44AA376FF96258E3FBAEF5E701AFC1
            5CA427993F2F2341301575CD7753AAEF6184EC87936F4259F0FD425D76AD65C8
            420A7F9E9867B8A1CD1E4F35E4672D488CE6E6E6E2A9107F70B9C51C611ED3D9
            9213E7CE9DBA6C772359413A7F5E98F1DF9CF778DE4A779D9C05C154D434AFD1
            8AF49D49D6C32D5BCCB10513FC79860892A4804B167380BFC3B8F954580F3D3D
            3932F29EDD6D990F66FAF38C150421EC6C3D30DFAA73FA4310E26B286B7131A7
            C0BCC196F8F34C130483CC67F163E8329415F9C11BD548B76F68E8758B1A362B
            ACF6E7592208AA9C698B394663973FCF5241301BEAB67E81D1F0A350C13638BC
            1965459EBC6C17738CA0BAFAC1325E3AF74892615618272E305A7E6DB63FCF36
            4162A459CCB9000DD3179877F6F84707FE675619D02FEA85C98ADCE251438433
            72D8AADF62D92E0806592F623167A91FCDC01F45A379947810B00BDCD61F6448
            2508C62C3F9A58F7A69CED4FE26978037AC361BBFF44415A416288C51C6D3EBC
            63593F5A063F8A8E0C8BD3D35BA94E7F4A92FC7D8930C1D7AC2AFBAD0C7F8E20
            BD20986CFD68D50D0DB78290BB61D0F9119C7F1B3AFF5D383EC274EDE0F899D3
            FFB6BB5E98821224C682F9FC108CFFE24BB8161243D93ECEE97354548AF2AD24
            EECEE0302479C182EA2C09CD9D9275425A908260363436DEA171BA8F72D2764D
            2F887109AAF614D1F82159279F98821764918E0E5675D6D708BDA207AA72AB78
            8B31DA56149C7B067AC39CDDC5CB94EB4790788586C982195B1C0A14C93A34A5
            28BF124426942092A104910C258864284124430922194A10C950824886124432
            942092A104910C258864284124430922194A10C950824886124432942092A104
            910C258864284124430922194A10C950824886124432942092A104910C258864
            284124430922194A10C950824886124432942092A104910C2588642841244309
            22194905113B5BC3FFBF282F62836EB73B607721B3AC50C10922F64576526D17
            E5641F0870AFD87282727E956EAC6F7C87138A232C5F229C1C2554EB2994B014
            852448656DD37D8491764A88085F81B61DE7D0D6F457146D02BC1FDE6D20897B
            889C279CF60469E8A4DFEB9DB6BB32CB21BB205555ADA5F486991D9C927678D8
            37A0AC00E7DC4518EF9C181E3E27DE48088A100FAC48C59E5577A22CA9F7E295
            5510B4A5A1D89CEDE328EB7518A1BA93EDD3953CE4514707AB189BD8C822C147
            12378424620F73428F9B155831176412245D1CF874FB74A50D0A9622B0E2E20D
            8C0CAC980B320862541CF8ACC2E6556F6EBA27AC91DD49BA6024B022E58E6E3B
            0C01DB04C9200E7CB60F6B4E812533D98BD7CAA0C3560BB218077E6910E348E8
            6F9DD3C72747DC1772B976DEA1575307568CECF4D967762062AB044171E0B743
            72A246342C0EBC71C18913BB6FCE811573C14C41E2816DE0BB213170DA651135
            DAE8D829A684EF8E075614739B844A88FD713D30B6F619B929BF1982A48B1B55
            3C1FE8316348B632C07DD2C08A607D7481F5F1663EF7304A906CE2469985E982
            C4481D5891FA28D1FB02A5C547FD030357B3BD76BE82A48B1B65F6B6E718CB04
            C144F65D27DA5EB8B930043E89B222560AA44E9FD7FD874CAF978B20F9C68D32
            0B5B04C18D52363DDD44752A7A0DB6E3A3015328E9278CF4A7DB143F1B418C8A
            1B6516B60A82C9C78F965690028A032F8D208BE4E0475B4E1061ED151585F716
            521C78F9044164EA4773AEBEE9344182CC3A4A2A19E16213FE2571A316BC087D
            B26EB42CB520988D755BD6731AD9F75DC4B42A475917A1160118C8D62E1C8BAD
            C5711C9229C83BC269F8D084D7FBAADDF54847C10812635D4BCB0AE76C701B34
            F27E28FDA61475380FBDA133585A7C321753DA2E0A4E108CF0A331AE41AFE1C2
            B7B49646979F9F873945E7A4C7E3B7BB7CB9F07F04E70821DD08627600000000
            49454E44AE426082}
        end
        object laBoxTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 147
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Box editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paBoxValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        ExplicitLeft = 10
        ExplicitTop = 115
        object paBoxMin: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 20
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 20
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laBoxMinCaption: TLabel
            Left = 0
            Top = 0
            Width = 43
            Height = 13
            Align = alLeft
            Caption = 'Min edge'
            Layout = tlCenter
          end
          inline gvBoxMin: TGeometricVectorFrame
            Left = 43
            Top = 0
            Width = 339
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 33
            ExplicitWidth = 349
            inherited paMain: TPanel
              Width = 339
              ExplicitLeft = 6
              ExplicitTop = -1
              ExplicitWidth = 339
              inherited laX: TLabel
                Left = 31
                ExplicitLeft = 31
              end
              inherited laY: TLabel
                Left = 142
                ExplicitLeft = 142
              end
              inherited laZ: TLabel
                Left = 253
                ExplicitLeft = 253
              end
              inherited edX: TEdit
                Left = 42
                ExplicitLeft = 52
              end
              inherited edY: TEdit
                Left = 153
                ExplicitLeft = 163
              end
              inherited edZ: TEdit
                Left = 264
                ExplicitLeft = 274
              end
            end
          end
        end
        object paBoxMax: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 46
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laBoxMaxCaption: TLabel
            Left = 0
            Top = 0
            Width = 47
            Height = 13
            Align = alLeft
            Caption = 'Max edge'
            Layout = tlCenter
          end
          inline gvBoxMax: TGeometricVectorFrame
            Left = 47
            Top = 0
            Width = 335
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 33
            ExplicitWidth = 349
            inherited paMain: TPanel
              Width = 335
              ExplicitLeft = 6
              ExplicitTop = -1
              ExplicitWidth = 339
              inherited laX: TLabel
                Left = 27
                ExplicitLeft = 27
              end
              inherited laY: TLabel
                Left = 138
                ExplicitLeft = 138
              end
              inherited laZ: TLabel
                Left = 249
                ExplicitLeft = 249
              end
              inherited edX: TEdit
                Left = 38
                ExplicitLeft = 52
              end
              inherited edY: TEdit
                Left = 149
                ExplicitLeft = 163
              end
              inherited edZ: TEdit
                Left = 260
                ExplicitLeft = 274
              end
            end
          end
        end
      end
    end
    object tsDisk: TTabSheet
      Caption = 'tsDisk'
      ImageIndex = 9
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paDiskValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        ExplicitLeft = 10
        ExplicitTop = 10
        ExplicitHeight = 173
        object paDiskCenter: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 10
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 10
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laDiskCenterCaption: TLabel
            Left = 0
            Top = 0
            Width = 33
            Height = 13
            Align = alLeft
            Caption = 'Center'
            Layout = tlCenter
          end
          inline gvDiskCenter: TGeometricVectorFrame
            Left = 33
            Top = 0
            Width = 349
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 41
            ExplicitWidth = 341
            inherited paMain: TPanel
              Width = 349
              ExplicitWidth = 341
              inherited laX: TLabel
                Left = 41
                ExplicitLeft = 41
              end
              inherited laY: TLabel
                Left = 152
                ExplicitLeft = 152
              end
              inherited laZ: TLabel
                Left = 263
                ExplicitLeft = 263
              end
              inherited edX: TEdit
                Left = 52
                ExplicitLeft = 44
              end
              inherited edY: TEdit
                Left = 163
                ExplicitLeft = 155
              end
              inherited edZ: TEdit
                Left = 274
                ExplicitLeft = 266
              end
            end
          end
        end
        object paDiskNormal: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 36
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laDiskNormalCaption: TLabel
            Left = 0
            Top = 0
            Width = 33
            Height = 13
            Align = alLeft
            Caption = 'Normal'
            Layout = tlCenter
          end
          inline gvDiskNormal: TGeometricVectorFrame
            Left = 33
            Top = 0
            Width = 349
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 41
            ExplicitWidth = 341
            inherited paMain: TPanel
              Width = 349
              ExplicitWidth = 341
              inherited laX: TLabel
                Left = 41
                ExplicitLeft = 41
              end
              inherited laY: TLabel
                Left = 152
                ExplicitLeft = 152
              end
              inherited laZ: TLabel
                Left = 263
                ExplicitLeft = 263
              end
              inherited edX: TEdit
                Left = 52
                ExplicitLeft = 44
              end
              inherited edY: TEdit
                Left = 163
                ExplicitLeft = 155
              end
              inherited edZ: TEdit
                Left = 274
                ExplicitLeft = 266
              end
            end
          end
        end
        object paDiskRadius: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 62
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 2
          object laDiskRadiusCaption: TLabel
            Left = 0
            Top = 0
            Width = 32
            Height = 13
            Align = alLeft
            Caption = 'Radius'
            Layout = tlCenter
          end
          object edDiskRadius: TEdit
            Left = 85
            Top = 0
            Width = 297
            Height = 21
            Align = alRight
            AutoSize = False
            TabOrder = 0
            OnChange = edDiskRadiusChange
          end
        end
      end
      object paDiskHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        ExplicitLeft = 10
        ExplicitTop = 13
        object imDisk: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A000010224944415478DAED
            5D097414451AAEEA994C143087C7AA1C0B1E8888B26A046692EC3330474F5040
            44BCD663055D7559F07A282B2EE2B578A38B2820BA8ABA0B467741349913A28F
            4C2762F0405151574156E510421220C774D7FED553B33BB0997B7A6A3AE17BAF
            DF54F55457F7FF7F5D67FFF517463980E10E47EF3E849411229C81113A8D2034
            184E0F82E31896C408471F3876C2B10311BC0363F42321E44B383E108CA831E0
            F1ECE02D47268079DDB86CB4384C16D005186111615206A7F2D3CC722B1CEF82
            40AB5A05E2FAC4E3D9C74BB6749055424A4A4AF2F28A8F9D2820341D4A41798C
            A41D707C0B0FD70AE9F643B89D3D6D0126E84438771CC48E88717D1B1C3E283D
            CB8B4D86376A6A6ADAB329673AC80A21959595F94D9DF27408DE0AB7EC77C8DF
            324164BD80043728B01E13E12B9372604B6D6D6D30569E23ADD6630C42DED918
            91F308412520890511D4BF8BA4DB41C8A5725058D4505BB32D4B7A4D199A1362
            7638C661053F09C1530FFA83E03548404B9140DC92DBBD3B13F7B2D82ACF0182
            2600C113207AF6217F07A17A5C21A0E09C753EDFBFB4963B55684648B9CDF64B
            19191643D019717A3FB417AF0841BCA06EADFB332D052B1BED1C420C681A9073
            2D440B22FEA2D5E11285041F6CF0FBB76BF90CA94013424AED760722C26B50D7
            1FCB4E1182C90AD2699899ED6AA3A2A2A24F9BD17435948EDBD1C1A5B4956034
            AF73F7AEC71A1B1B3BB3F94CB190694270A9CD391BDECAB91036B0739F60814C
            876EE97B3C050D75288EB91E889903D11322FEFA1063654AC0EBFD88E7F38591
            3142264F9E6CD8B6A7791904AF8CC87E49511E9E914BBD1C3AE6E9A5A05B8198
            3F42B4373BDD098A78B4304F7880F7B36684104AC6F7BBF7BE8431BE8A9D6A83
            EA607ABDD7BD94A770B160763A07E120791E82B688D31B88114FAA77B9BEE3F5
            5C6913C24AC62B10BC829D6A420A12A535EEF77909958CFCA536F17A68EB1E83
            70213BB713617C85E475F9B93C50BA1998ED8EA731C13358B409C28E80DFB59E
            8730A9A274CCD8814450DE80BEC779EC948C319A1DF0BA1FC9F6B3A44588C526
            D2F6E23516DD0B64D8F5464618D01B3BA23DCFF40C8C8FA6469C5E24955BA6A1
            B973956C3D47CA84586C63CF82174942A18651818EED04C9EF793B5B0FAE15A0
            0ABB01AAB00588CDAD818256EC2D2EB8E6B3AAAA8E6CDC3F2542D4B7C9984FBB
            8943582E0F485EF79C2CE94C7358EC4E2BBC602B51688699C2D571A46952E3EA
            D5FBB5BE774A84C058632E8C35EE655978A4727365368B7536506A758E80C16C
            0D629F00A0D4AC3D22D83EB6B6B6B64DCBFB264D8845144F4532DA8842B3AD2D
            48C91B2AAD79FBDF5CB4A631CC36DB500119DC40C6001A0765BD650AB64F8A37
            F1990E9227C426BAE04764D1DB249FFB293EEACA0ED80BB80E82C7AB27307941
            F27A6E406AA1C93C9222A4CC2A8E56305AC3A21FE507DB4768F9B6E40AE82C32
            F45B6A51789212937940CADD5ADC2B2942224B07168835E0F1AC49E67A3DC36C
            735660A4B629A10F63185F0983C7BF67FA3E0913621E239E8B05D4C8A20D5055
            99792B29DB00522E06526000A9EA6D1FBC946678293FCDE43D1226044AC70AF8
            B9548D103211C61C2B792B8807609CF220341EB3691894B7B91DC9231B7DBEBD
            99CA3F2142D4CFA5D8F803044D707C0EA3D733BB5B37375184E6EE5AAAE1AD74
            B0532BA1B6B81865A8914F88108BD5792334648B42313253F2791EE7AD189E80
            9ED7D1D0F3FA008227319D4C059DBC9889BC1323C426AE859F0A3894A04006AD
            F778BEE7AD14DE303B1CA3B082697798DA8C35C178ECCC4C8CC7E21232AAA2B2
            BF6054B640508042F99EE4779FCF5B19B9028BCD390F4AC72C167D07AAAE0BD3
            CD332E21169B630A247B414D4CF0B480DFF52C6F45E40AD89CDE06080E65A7AE
            055296A593677C42ECCE97A057452D379020E3D3EBD6BABEE4AD885C4299ADD2
            AC2085565D0650E62E53B07D300C969B52CD2F811222521B26DA78FD04EC9FC8
            5B01B908D0D17CA41A01D2F1227A34E075DF956A5E310961ED47B8017F1D08B9
            8CB7F0B908A8BA8AA0EAFA1A8566863B0C481E9AAA315E4C42601034093AD774
            640AED399951EFF32CE02D7CAE024A092D21B4A48052F16B019FEBAA54F28949
            88D92EDE8D097A88860582C6D4F9DD6B790B9EAB183679B2A9604FF326089E02
            07510432A2C1E3694C369F98841CD4A063A55F9DD7FB036FC17319A0AFC9A0AF
            D769186A9637EB7DEE4B92CD2336213631407FE06881F6A31069F40DA01B015B
            ECE246D0D23044ED0C0C6888E4767F9D5406B1FE84366427B3CFDD008494F096
            560F009D5D073A53A751A0DD7D16DADD69C95C1F9D90B97305CB3A891A210B70
            BC0D848CE32DAC1EC0DA926F21D8178EFD1D41D3C0C6DAD5BB12BD3E2A212536
            5BA109199A428952EF35F444586C8E59A0B579340CA5E41E28250F257A6D5442
            D8FA8E2D2CD3A48B5E4F46F9051714CBED41BAECA2171C5F41ED42CDA5126A7F
            A31232CAEA1C2E60F271289576DF90BB2BA043F437C4EC9D052458EA7C35F589
            5C179510CB187124E4D4A046089A23F9DD0FF016524F308F7154620157D37032
            354C74424296161B5028C7FB81907B790BA92754545418DB8DF974DA892E0EDA
            5D9427F44D64ED498C2AABF20C180CAAEB00A1F27B040639B3E265761807C362
            159F020DDFA24608199788ED73F412123210FB8A459F8286E936DE02EA0D9631
            8E5224E03A3542D042A865FE10EF9AA8848C7038061815BC95257A2EE073FF9E
            B7807A035BCC44DD8114A3506FEBB478D7442584AEC5EBADE05616AD82CC2EE5
            2DA01E61B6896F809227D1B001C9A7C49B968F3797B5077E8AE090809052DEC2
            E911A536C7EF08C28BD508C137497ED7E258E9E3CCF68A9FD2893248F43D5459
            BFE42D9C1E115A2E277FC7A2713FF2C52B21D496957A6290FB1717E4575555C9
            BC05D4232C36C736E6E3E56B206470ACB4714A88636978CD1DD47F03A1FEDBCA
            5B383D025EECD5F0434D848892271435D4D434474B1BFB8BA1D5793BC6E4091A
            2602195FEFF1ACE62D9C1E01E391FB40D3EA923F2C90F36379B5884948E47A10
            EA2E0386FFF7F1164E8FB0581D17218CFFA94630BA55F2BA9F8E963626216CD6
            F267966E15D47F17F1164E8F18E9709C645070A8BB8BC962C9EBB9295ADA64EC
            B2B6022103790BA747B0792DBA58943AE48969721A9790C8818D121406E8C12B
            5B2E025E6C6A88DD9710F471BDDF7D76B4740998928AD3A001792614CB9CD97D
            4F0310427DBF8CA0E6A630A63B2E5ABAF8D6EF76FB6081089B59E21590D9E5BC
            85D323A061FF0734EC13D5C8BE825E925475A0AB7409AE0F717E03A5E36408FE
            0C03C4E30F0F10930754FD4B40D97439350A060D27AEAFADFEA9AB74892ED879
            0E7ED49E018C47CC301E69E02DA0DE003AA466B8EAF43B560C83026BAAB77495
            2E2142CC76E7784CC82AF5028C9E0C78DD77F016506F28B58B4F40834EFD3E22
            991886BCEFAFDEDC55BA840861B646D48C945A776FCF0FB6F7EF090E033289C8
            D556305A3F2BDA72EAC49745DB1D8B10C137B2CB9C92CFE5E62DA49E10397D42
            145452BFC6BDA1AB74893B0EB0DBCB3011D6A91912F26ABDDF73356F21F504B3
            557C1CAAFB50552F90A192C7F34557E99271AD81A161A2DFD8A9B9FD3E566DA5
            BC74ABA721B297156B254172BE4EACE29FE08AFBD50B319AC5C327A15E11E909
            639F40FA44DBBD213942420BE6E93711EAD68F36EE83B476E8D55D008DBA9B79
            7FE8947C6E53B47449FBCB2AB589CF12846E66174F8191FB5F790BAB074009A1
            66B9C3E1F81108E91B2D5DD28494DB6C27CBC840FBD074E6F20BA9DC32ACA7FA
            3D4902B4FDA5163CBDE2395F48C9E762E40C303426974A5E57156F8973199136
            6ECC23DDF5D1D2A644C82887A34450F07A76FD37CDC5056764CB8DAA1EC1BC9C
            FA681846EB77D5FBDD8F464B9BB2DFDE529BF35582C86F58B4DBFB5E4C0716BB
            780B545521FDC4F13596322121A70232B425F84888EE8116E5D44CED94D3DD00
            EDC79BF0437D6AC55DCD9CA6AB7107143D3C9365355FF2B96EE72D7C0E8236E8
            74271FFA512AAE7D6F5A841CE252422602293B3C357F30E8F6808A01852612E3
            34E86A92746F68B63AAEC518BFC4A29B8AF28473796F8A924B38C8E50646D704
            BCEE5762A5CFC8862E669BE31D8CF0D8508E87D72346027423816EA807575921
            C17EF13622CB0821CC6B102D96D4DB431029A84C271BBA680A3688A6553A567D
            E4FB5C62BC6B32B60795C5EA9C0AA523BCC5D1D68EA0A9249905F3DD113034B8
            078606EA625942C86FEBFD9E97E35D93C95DDA686F829A4B4E6071B7546E19DB
            53A755D8EA29FACD836ED5D7D681E41312F1EF9BD16DF398F7073A821FCC72EF
            56FB8A2403E8EC5C069D9DE5349CCC07BD8C6F2CD9C5CE3B937AA0176C5A5B50
            5F59E720BA6E4A20C3137549AEC94E9F87EC4DD586B0E094BC35EFF2D652B610
            E93400E8582DF95DE313BD56B3BD700FF169BB1763A5225776D3D412744751D3
            D1C77EC87C66011F4A79BDD75B97E8F55AEE168D2D76C7F311BB9E6D4706549E
            AC432FBDC16C15EF840160E8D37692A58342D3EDBBD59E4653CB726847C2AEEE
            7E44C8204ABEEA8D7CD4A52DD8770FEA77B10FB0714016D0B0F73D9E6F93C943
            F3FDD4A9F7E736637E35DC68343BF53334F563BBDBC0917573A9AD9A95C693F5
            931586E68450948C1BD7CB74A0834E4187F7566F45185FC46B7B532D60B6890F
            8332C30E94373517179C93CA47BBAC104241CD510BF7342F230885D769B76344
            66047C9E25D97A06AD60B13B2742B54C5F38AACF568508A31AFC359B52C92B6B
            84A808F9715C8898253DC38BF9C1F6697A3527620E66E8DE5C47215A53617C59
            3A3606D9258481F544FE8C42962BF4211A1523BE84E7B6D9A9A0D4EAB4104C28
            19A1DDDB107E5CF2B966A69327174228D8877FBACB59787957337413EF846E22
            ADC272DE3F302B19D4D305DB4A0FBF2C9599A7A43B77C78D100A3A6D8F8D7215
            FB5E107EA0754162981A6DFD442EC06213AF81776611B32780F7882C1F505478
            55265696712584A2B2B2327F4FA77C0F90427B2879ECF47E28230FE7CBEDF3A1
            6D694D27FF4CC262997C24E9DDBC1094765DC4E965FD8B0BA6646A991F7742C2
            2817C55FC9B2EA11FADC88D33FC1133ED8B17BD792C6C6C64E9ECFA77AB510D0
            82F094084086767076C0ABDA5865AC8ACD194228E802FB8EBCFC3B0851F7093C
            2AE2AF6FE049E70BFBF397D5D5BDD592CD6762A36FBA2B5DA403B71D0241976B
            B15B444E1112C6AF2B2B8FEB0C42354630ED1E475A8AB7C0BBB88C607961BDCF
            F7B996CFA07E46C0C169D040D0EF18BDFEFB07C1AB1131DEACD50ED939494818
            D4478820A3FB31F4EDD1FFDA97B06636423DB18A08686583C7439787A55D6DD0
            17410E2A4E42C85450CD4106D174574F788EDBEABCAE6A2D65CE6942C2B08CB9
            B01F3274DE082AA72B904EF8FF1404DE56DC006FEF0758901B6545F9389E7507
            9D3928DAD5729222288341D16618D189900F6DBF844334B40DBAE74F371717FE
            251BF6CBBA20240C75357053CB244CC8E504117BB8DB1905A03CB213D25062C2
            26AE8558DD2C48F523491DE918635C5F0BF75968923B566673C5B1AE0889843A
            61D9D62962858C277417528C06A599651BA8E33DE850B8B141A98EB628536BE8
            96904311DA4039EF3C18A49560824E8753BF8012D21744A43301D4D4353C9EA1
            3E46684FED3B18FB6C8692B61946D99FA3D6A302D1FC8F6413FF01B1012CBF47
            636B2F0000000049454E44AE426082}
        end
        object laDiskTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 155
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Disk editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
    end
    object tsCylinder: TTabSheet
      Caption = 'tsCylinder'
      ImageIndex = 10
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object paCylinderHeader: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 382
        Height = 100
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object imCylinder: TImage
          Left = 0
          Top = 0
          Width = 100
          Height = 100
          Align = alLeft
          Picture.Data = {
            0954506E67496D61676589504E470D0A1A0A0000000D49484452000000640000
            0064080600000070E295540000000473424954080808087C0864880000000970
            485973000038C9000038C901774E6AC20000001974455874536F667477617265
            007777772E696E6B73636170652E6F72679BEE3C1A00000EE44944415478DAED
            5D696C5C57153EE7BEF18C133BB6D3245D5852546893B674210E89C74E9AA45E
            264E93B6A0A6421490A8A04820B1FC01A482082090E00FBB844A8590282A4D0A
            8506C7DBB88DD3C463C7758094344E6851EA744B9D3ADEED59DE3B7C7716FB79
            3276BD247E76E67DD2D55BE6BD37E7DDEF9E73EEF6EE615A00D8585D5D6098E6
            6AB2F87A4B642533AD12E16B59F14A16598EFD7C6629C4A5CB84281FDB25C95B
            155261DAE3FA90ACE4FE08130D623B80FB7AB13F24CC1748A81B979C136C15F3
            7952F29A69185D6DB5B5FD4EE705CFD71F9595DDBB8C968EAC1132D69225375B
            4C6B90311F41E6AFC6CFCB9DCE88242E80A42EC8F42A0B7592E2934C66674E34
            DA79F0E0C1C1F910E0B210B275EBD6DC88D7BBC132D57A94EC629CD2E9464A94
            E8B9204A8912DF0BD165FCB4244B3617D8CEE9772BA28446E5CCF17FB5C69D66
            E20E4BE89841D29E6386DB41D2E8A5CEBB4B42487171718E6FC58ACD9645DB20
            F4169CDA80E49BE6ED6F09C96BB8AF0BA5F32C447A13249E8F9B1232DF81C9EA
            8139E9ED2F28183CB16F5F6436F2DDBA7BB7B7A0BF3F1F66B1C812CF0A56B42A
            651A21F375492DD5E97AA46BA7F9D85168F85114B16665D1F3A3BDE70F777474
            44E79A97B326A4B8A2A2D0C7C6BDC8C49D380CD0C5B6DC8E185227D27164FECB
            4AE894B0E754518E9CAEADAD0DCFF5252E25B4768F18B93729456BA08330B172
            0B4EDF8674339231C5ADD05A6A60E6FD6189EDEF0806FB66F3FF332224AE09CB
            57EE80AD780887BB9072335F296FE0D1CDD809B170477869CEBF3BF6EF1F9EFF
            ECBD7428DEB56BA977287CA7282A8636FB714A5B82F74D72B93665CFA202F1A7
            684F77ED4C34675A846C282F5F6150CE23C4D65770CBFB335CA2ED7A03CCF601
            F24873A8BEFE15A733703EB0B1B2F24626B5852DD941CC9594F05713C1F43A89
            FC860C7E0CF9D2F35ECF9C92107F20701599F26D5C06226869DACFBDF0AB7F61
            92BD851E4FF342333DF38DEAEA6A5F6F54B6A2D0EE46C17C802E36E1C3B02CBF
            F2F83C3F395C537361B2E7642464F7EEDDC6D90B7D5F856A7E97265649F14C6E
            04098F7963E19ACB51CBB81210AF651ADE9D30595FC261394DCCE71E1CFD2054
            E6FF15EDD963A5DF7B1121A577577F9894F507E4FC26DBE9288EFF20A27EDED6
            54FBB2D32FBC98505A55F551547CBE0EADF91CD9ABDF42870C363F7F3818FC9F
            FDFA0984949507B6A1C1F60C8DAB9BAECCEF1583BE932D7EE17241FB1B25EA47
            D8D5E62C95EF30FBEAFE50636D73EABA3142FCE555F7C331FD9952ED073823CB
            9287DB9A1A1A9D7E992B09FEF2C076F8DEC76D95A3304CDB83AD8D75CFEA8338
            21FE8A1DA8679B21ECE6252F0AFA62E1DDF011BD4EBFC095884DF7DCB3DC1C35
            9F063177274F0D2A934A8E3C5F7F82B5037FFD42FF719CD40D20EDB5FF32B0BC
            E0D3B36D15BB981EE2BD073D7D7F8655FA44FC04D30938FADBD95FB91DD534D9
            9BB84C5E8A2CF1952CF646DC62C1ED55557979C26DD0825BF531CCD503202470
            0027AAE357601B6AAAAF735AD06C4259E5F61D96484DF2B086FD15813394E854
            EB0B05EB759B4366FB7017B382E640FBEA02E4FC19AD2161EC78C1C3BBA160C3
            4AA7A5CB468090016CF245373370A09D371A2C2211B296CFB697D2C5EC80567D
            51D8E3ED81A2C46BBC5C521118E2643F155A818FB636D6FFD86921B309A515DB
            BF23243F4C1D6B0D7907DB55C9E3300B6F6E69AA6B775AD06C404955D546B6E2
            C314A9C1BCB8C97A133BD7D9AE3BA7D8DA79A4B1F145A705BE92515ABEFDE3C2
            F20FEC5E6D3B1D27E42D4A0C5BEA9EDBD480D3204CDA23A1C6BA279D16FC4A44
            4979D543CCFC5B4A8D9F080FA0D5BE0C7B969D90FFA265A2A7C86C18BB93F969
            45E6D7A02D6F3AFD125702FC77EF7C3FA9E82FB1FBC9D439F88F56B80941DEEB
            51C80984740E29599F67D21FC79AF3090C83BD5FF8A2919FBA7D5BB343A22695
            FB2DE4F7D750CA5373CAE2DD54D125DECF798723B520E42E4A12F23676AE41EA
            44C3500FE453B23B45ABD455B6E7A2AECC4F92B27E166A68E874FA2517033655
            54DC1023E311D462F5405591EDA73E26F9664BB0E1317DE02F0F346722E42408
            B92575C7E640E0BA98C97BC0E3C338F4D81E66819820B33CE18D869F99AF0964
            8B05D086FCB0C7F749B42A3E23121F2DB4CF458B829CC74D897DBFADA9E95CEA
            24383884CD664A12A27FD09E7E022163175755AD15931E85137A1087DEB49F87
            900E88484D8ED738F0426D6DB7D319E204365757AF8A46CC1DACD44E5816DD2F
            989776899E6FF09429C68F8E361D389D7EBF8D10D34EC8CB20E4D649FF141A13
            35E5CB4CAC3526D3F4173D3EDC0EBB78D0603E14F3F0E1853057F672203E278D
            8C4DDACCE07DB7C219ACA78CB332E50D26F57834A67EDB7EF0C0DB933D6F5684
            A4A0C74FBA7AFAEE56CC9FC5E1FD48CB26B9D4443A01813BA0BE1D4A54C78032
            5F3ADED030E47486CE04DA04458CDCDB50112A465DA85898D6E1B4CEA7C926CD
            E97EA967F0DE7F6CDDE47F2ED3448674A413926AA94F8B103BF4D4979E887917
            2BDA89AADB3D38F5E1F7B845F72477C1079D826A9F84B69D16B2BAD8A03361CB
            3AEB543F9A2EF15EF2AE1615FB105ACED723F36F54C437C307ACA1C414D3F7C2
            2B78B31A8BA466F0AAC2E6990EEE6526448F5835D67F742E2F865AC56A8B8D2D
            A85B6F416347CF5AB98966363B529BB8B7704337FC5237AADFE7502A7B600CFA
            2D917E10A8FBDD86ACC427077118A40663CA8CCF0CF458468E49D6D86435D890
            4294803CC893078D2E80512D4009D735C76BF19C95922888DAFC2E9B818CBA50
            9D825C8749717394ADE6F68686B373C9B7D28AC00BC9593E26E3A01B072B2F05
            21E9D0252F578C75A2681D4A9B5675541A648DBD2EBEB02123905557F14FC2EC
            1EB3843B24878F5D6ADF682324364E08D17F60B26EBBECEFB8678FDAD0D272BD
            61F21A14828FE0A557A3E4AF96F1D9E75A16EF1CFF65BA8069812612774163BA
            A0494874169AF48AE5A1CEA3A5A5AF4DC707CC15CE12320DE8966D9473AF8919
            B40A25F32A16C947432A1F25B408FE2A5F244118DA4245246AA249641837E1DE
            C4EF14118B06154BAF100F0A33DA4CE6BB46CC389F23A3E7164ACFC30442E043
            CE6367052D2042B20D9310222F85820DB73B2D5C36C25FB1FD30F2BF8C9284BC
            4BF13E2B9710A76023246A23848EC364DDE1B470D908979005867442F4573D7A
            3E964B8843F057068EA0B9594A76425095FC776B53FD9D4E0B978DB01112D184
            E8CFAB8A5C429C43464290FE0593F531A785CB46B8842C30A413A2BB0FF4276C
            2E210E011CB4E80DA511F24F10B2CE69E1B2113642C29A103DB6A0176D710971
            089311720C84143B2D5C36C2256481219D103DFAA587305D421C424945558889
            4BC84E081375B404EBD73B2D5C36C246C828A73EA77209710E190921E21743C1
            BA8F3B2D5C36C2256481219D103D593ACF25C4398083566C36D24442A81DB5AC
            0D737BB48BD9609C1019D184E8B9B6FA2B5C971087909910A6A3A1C6FA8D4E0B
            978D70095960F05706DA12DF76C609A91A8ECFB57509710CE384D0F03821446D
            F021254E0B978D482324304289EFD35D421C424642F4F7D2ADC106BFD3C26523
            5C421618C0C1516C74A33C4E885E52C3E712E21C6C840C8D118214820F29755A
            B86C443A21FA1B6AFD018C4B8843C84C08530BDA21654E0B978D70095960F057
            6C6F472B5D0F0E0E8DAFB9E812E2186C840CDA16C1E423A160DDA6B93EDCC5CC
            914E88FEE8DEE312E21C3212C244875B82F59B9D162E1BE112B2C0904E880E69
            67B8843887F46A6F9C10A417D030BCCB69E1B21169035401BDAE955E7CCB25C4
            21A44F034A10227428D454BFC569E1B211E993AD5D421C46FA276D7AF9217609
            710EB6C567A2E384B85F50390668C83FA110FA93F4F8127FA9883AFD20A4702E
            0F76313B9454047AA111851C5FE2AF32A0E3987F104A0242EAF4E7D16EC8A3F9
            C545218FC6828289253B5A9F6BA8755AC26C02FCC73DD0807F240F6B2686CD63
            3A31C4B271B1ADADBB58915C96BC8D923124E361F3D2034B027F2BCA519FCAF6
            70DC971B7ACDE3BEA8B517DA716FFC442AB0A4DE2FDB16B8D532484FF84D0518
            79CEC8351E982AEEB78BD943C7A917939E46E66F4B9E1AB04495E848DC632B7A
            96546EBF97459EA2F1283B6FC2A77CC1F5299716499FF13B1A0F3335AA4D554B
            B03E1E5C72C212ABFECAEA2DF0EC7FA3F15817A880D15F0D931F3DF27CDD29A7
            5F663143479920937E9C162CE78212BAEF4853FD0BA913172D03AE839098A47E
            8F9FECADF6985E5C5E847FDED65477DCE9975B4CD81408DC615AFC0D14ED87C8
            168705F9F93C79F8E1D6BABA33F6EB33AFCBBE678FF21F0E7D59EF51624DDF71
            C0BF08598FF170E1B3A1D0BE11A75F7821C2EFDFBD8497F6DD67313F62F31329
            740BC9F75A830D3A82D1456DBE2917CA8F470D60F52D90F055BA384849BF8EA1
            C4427B7D66F82030EA744638095461734795779B627E50381EF4AB20ED924164
            F62FCC1CF5D3A9D68E9F56E4021D903D361AFB22337D8532876FD0ED9620931C
            605335678BBF49F805B5855976A070565032626A1A5E8322FCDA178B3C3E9DA5
            CD67124A4297024FC4E30B582C9F8166DC374594031D4DE6909EEBA5230A2C89
            8DFE6BB1C7AAD28DB8A8E1FB98A5681D0C8D9EBFA687BBAF9DE4721D8FFEEFD0
            9627DE57B4AC7EDFBE7DE674FF674684D8B1B1BABA8023E62E4A0473095062A9
            D9C9A07B944FE1CF8E5B2427F1B7273D069D32FB0B4E2F343F54BC6BD752DFE8
            E84D96C56B14AB9B51BAD7A2F4EB15BF75701735C5AD1784A51E79B15F8DF8F6
            1F39F2ECC06CFE7FD684D8A135279CB3A40CED986DF1602E241B67102344875C
            EA221D26025B98C5B72DE2736C59E7C5A06E1533CE872D4F9F379C3B345BF2B4
            938DF846F37C2A566879CC956CEAA80BAC83D85C8D7ABD2EE530C3BC5A87CEA0
            89A150A7808C0871AB223E44CA7ACE1B89B4C00AC4E69A9797849074E86E810B
            B1D87A26B51EEAAD977CD2499730638E8FD69AD687CC804950635D3B22122F8D
            C8645BA41CD10D5C5D28F490829AD9DF5C041339D5897739866D076A992F0E14
            15B5CF34B4D174705908C9046D0A7286226BD9E03522D62DCC6A2D72F20608B0
            3A19BFC4714096F3F1802ECCAF42C64EC8F8B298722A9AE7EDECD8BF7F789E64
            701E9A2CCF70EC43868A7D0085F91A4B6425B4EB6A98BF6B60068B285EF2B908
            A53E0F02E74BAACF2D8122DB7BE87AFD584D06270745075A26462D507A510006
            84B997611251CADF818FE846E17FC7B43CAFC7967ACECC57A64F85FF03FAA9C1
            BE4B7E4C530000000049454E44AE426082}
        end
        object laCylinderTitle: TLabel
          AlignWithMargins = True
          Left = 110
          Top = 0
          Width = 211
          Height = 40
          Margins.Left = 10
          Margins.Top = 0
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alClient
          Caption = 'Cylinder editor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Layout = tlCenter
        end
      end
      object paCylinderValues: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 110
        Width = 382
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        object paCylinderStart: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 10
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 10
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object laCylinderStartCaption: TLabel
            Left = 0
            Top = 0
            Width = 24
            Height = 13
            Align = alLeft
            Caption = 'Start'
            Layout = tlCenter
          end
          inline gvCylinderStart: TGeometricVectorFrame
            Left = 24
            Top = 0
            Width = 358
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 24
            ExplicitWidth = 358
            inherited paMain: TPanel
              Width = 358
              ExplicitWidth = 358
              inherited laX: TLabel
                Left = 50
                ExplicitLeft = 50
              end
              inherited laY: TLabel
                Left = 161
                ExplicitLeft = 161
              end
              inherited laZ: TLabel
                Left = 272
                ExplicitLeft = 272
              end
              inherited edX: TEdit
                Left = 61
                ExplicitLeft = 61
              end
              inherited edY: TEdit
                Left = 172
                ExplicitLeft = 172
              end
              inherited edZ: TEdit
                Left = 283
                ExplicitLeft = 283
              end
            end
          end
        end
        object paCylinderEnd: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 36
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object laCylinderEndCaption: TLabel
            Left = 0
            Top = 0
            Width = 18
            Height = 13
            Align = alLeft
            Caption = 'End'
            Layout = tlCenter
          end
          inline gvCylinderEnd: TGeometricVectorFrame
            Left = 18
            Top = 0
            Width = 364
            Height = 21
            Align = alClient
            AutoSize = True
            DoubleBuffered = True
            Color = clWhite
            ParentBackground = False
            ParentColor = False
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 18
            ExplicitWidth = 364
            inherited paMain: TPanel
              Width = 364
              ExplicitWidth = 364
              inherited laX: TLabel
                Left = 56
                ExplicitLeft = 56
              end
              inherited laY: TLabel
                Left = 167
                ExplicitLeft = 167
              end
              inherited laZ: TLabel
                Left = 278
                ExplicitLeft = 278
              end
              inherited edX: TEdit
                Left = 67
                ExplicitLeft = 67
              end
              inherited edY: TEdit
                Left = 178
                ExplicitLeft = 178
              end
              inherited edZ: TEdit
                Left = 289
                ExplicitLeft = 289
              end
            end
          end
        end
        object paCylinderRadius: TPanel
          AlignWithMargins = True
          Left = 0
          Top = 62
          Width = 382
          Height = 21
          Margins.Left = 0
          Margins.Top = 5
          Margins.Right = 0
          Margins.Bottom = 0
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 2
          object laCylinderRadiusCaption: TLabel
            Left = 0
            Top = 0
            Width = 32
            Height = 13
            Align = alLeft
            Caption = 'Radius'
            Layout = tlCenter
          end
          object edCylinderRadius: TEdit
            Left = 85
            Top = 0
            Width = 297
            Height = 21
            Align = alRight
            AutoSize = False
            TabOrder = 0
            OnChange = edCylinderRadiusChange
          end
        end
      end
    end
  end
  object paButtons: TPanel
    Left = 0
    Top = 211
    Width = 400
    Height = 35
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object btOK: TButton
      AlignWithMargins = True
      Left = 320
      Top = 5
      Width = 75
      Height = 25
      Margins.Left = 0
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alRight
      Caption = 'OK'
      Default = True
      TabOrder = 1
      OnClick = btOKClick
    end
    object btCancel: TButton
      AlignWithMargins = True
      Left = 5
      Top = 5
      Width = 75
      Height = 25
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 0
      Margins.Bottom = 5
      Align = alLeft
      Caption = 'Cancel'
      TabOrder = 0
      OnClick = btCancelClick
    end
  end
end
