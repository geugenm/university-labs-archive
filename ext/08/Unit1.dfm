object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Lab8'
  ClientHeight = 349
  ClientWidth = 749
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object HParameterLabel: TLabel
    Left = 24
    Top = 157
    Width = 89
    Height = 13
    Caption = 'Argument step(h):'
  end
  object BetaParameterLabel: TLabel
    Left = 24
    Top = 93
    Width = 68
    Height = 13
    Caption = 'Upper limit(b):'
  end
  object AlphaParameterLabel: TLabel
    Left = 24
    Top = 29
    Width = 68
    Height = 13
    Caption = 'Lower limit(a):'
  end
  object OutputResultLabel: TLabel
    Left = 333
    Top = 47
    Width = 44
    Height = 18
    Caption = 'Result:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object FunctionSImage: TImage
    Left = 514
    Top = 99
    Width = 215
    Height = 64
    Picture.Data = {
      0954506E67496D61676589504E470D0A1A0A0000000D49484452000000DC0000
      0040080600000071FE19B9000000017352474200AECE1CE90000000467414D41
      0000B18F0BFC6105000000097048597300000EC300000EC301C76FA864000008
      C04944415478DAED9DC9AF0CDD1FC64FFF07DC6BD82036248690D8191224889D
      312C48C4CCE20A62232C090B616161B610246676A6043126120931242436AC10
      FC07BFDFFB9CE4E9541FE754D7D85DD5FD7C36EFDBB7FB76D52DE7A9F39DABF1
      BFFF3042888ED090E084E81C129C101D44824BC9DFBF7FCDD6AD5BCDA3478FCC
      9B376FCCB56BD7CCEEDDBBCDDCB973CDE3C78FBB7D7AA2E248702979F0E08199
      34699259BC78B19932658AD9B76F9FFDF9F4E9D38D2EA56887049701EC72C387
      0F372F5EBC303367CE342F5FBE347BF7EED50E27DA22C16500025BB26489F9F1
      E3877DBD7FFF7E3338386876EDDAD5ED5313154782CBC0B163C7CCE7CF9FCD89
      1327ECEBA953A79A3367CE9857AF5E99F5EBD79B61C38675FB14454591E03230
      6FDE3C3334346456AC58615FAF5EBDDA06512E5DBA64162E5CD8EDD313154682
      13A2834870A2054461E18BDEBD7BD78C1933C6FEACD168D8FFAE5AB5CA5CB972
      25F3777FF9F2C56CDEBCD94676FBD51290E0840591D7A54B97DA94C7A143875A
      FC504665CF9D3B67366CD890EB38DFBF7F37070F1E34BF7FFF36A74E9DEA3B7F
      57821316F8A1030303CD405014EC4C13274E6CA641CA3E5E2F23C1096B462E5A
      B4C8FCF9F3C7BBE3B47B3F0BD8E9C68E1D6BEEDFBFDF57E6A504E770E3C60DB3
      72E5CA52BEBBDDA53E7FFEBC397AF4A8F9F0E1837D8D7231A41B264C98F0CFFB
      23478E345BB66C317BF6EC69110193F04F9E3CB1AF510D83D2B3385310690D98
      93070E1CF0BE8F3CE3EDDBB7CDFBF7EFED6BA445F09DE0EDDBB766DAB4697617
      C4E7AE5EBD6AAE5FBFDE8CE0E29C376EDCE815D6F6EDDBCDA74F9FFAAA604082
      F30073070B076CDBB62DB3D903DFE7C89123D6670171971A8B18BED3C3870FED
      027EF7EE9D2D17E382C6623E7DFA74CBFB0B162C3093274F6E2E58FE0E7D2DEC
      222C410B053B682EC6ED34AE2021EA59B366B5FC0ECE0FE2C7DF8BF344510076
      4688345410C09BDBB76FDF9A019A5E4782F380853A63C60CF3F3E74FFB3A7AC7
      CE02162C76A5D0A5A679153A0EDFC7EE165DBC5CB05CF8DC4DA2BE1616FDD9B3
      678382E37750D8A163F31810E8B265CBCCE5CB97BD9F8F8AF1E6CD9BB1372BDE
      208AF40DAB8E0417800B07C07C436740D6BB308510BAD4ED163DDF7717A66F47
      C38D02C0DC5CB76E5DD31CCD7A6EBC0EA8ACC1F18E1F3FDE62E6BA30A2895DF5
      D9B367B13E9F7BFEFD80041743D457C9D37EC38515BAD4ED163DDF7705E95BB0
      346361D661878649EC86F9D31C3B7A0D4012137BD4A85156F0219F30EEFC7B1D
      092E06E6A61880286B6170D16317F1ED1C3E5311C42D589C3B4C3AFC1E12CDA1
      C5DF4E70286303B8D9C04F833F1AB76460C2AE59B3A6C5B70C21C1897F605081
      84CCBE3C70E18502173C0757380CD7538808F66CDAB4A9E53B2098D1A34767F2
      E1681ED277748FE73B4F7C76F9F2E589D208F2E1849768AA20896F920508E3D7
      AF5FE6D6AD5B76976345064406DF9191532E4E4629E7CF9FDF14138BA89F3F7F
      6EBF23C90E1217A574054101E29C605AE2FC685EB2131ED5233065F19D080241
      C44F9F3EF51E5F514A110439A393274FDAFFCF932A0881058BFC198F81BA452C
      6CEE3AAE6F86400E3E1F6D07624492290DDF677C84F2703437A33B157F86F363
      69967BB3885E2FFC0D6EAE307A4D9587CB08EE86B8E3B9264D1CB8C321AF840B
      5FB499563458F0B86B3355D04B151234153BB9D3A8D2C481F638EFB8C0BDEB12
      38D330B3E2C2C52120D41D3B76D80EEAAA774CD3C4027953055503BB140A973B
      55DB08F317E4E93EA8235EC1416CB367CF6E291D0A39CC2C37CAE3D770F7C03F
      769E047327A049057A6952575CB740D1C78199AB6E810830F1E0E8B276AEF9E1
      46A3C5ECA059504494A91B664D56B01B949D2AE816F877806B70F1E2C5C2FF1D
      D40F17101C1297D1E85708B7A8352F382EEE7E55372DDDD2AF325205A237F10A
      8E77F0502296C4551464AD1EF7EDAC55843B32282B55207A0FAFE0583F87C0C0
      9D3B7782494EF85D21932A4BF5B82F0C5D65587901CA481588DE2318A564890E
      CC26B74A1DB8ED2321D2548F876A06439F4B4A59A9460400E6CC99D3EC5FEBA7
      8A09918DD83C1C7C95B56BD75AF3D23501930A2E4DF57852C1558968E9579636
      1E0EE811E5DD18AB44DBC43705E34E6C4A2A3890B47ABC8E8263002549B1AE10
      892A4D7C49CA763E1C49533D9ED487AB8A49091060FAF8F1634F25C14579B408
      0E5142547A474D4726A57D3B54BB9D2B6DF5789DA29480BD62F2DD44525A0487
      22D611234634939EAC5847CDA3EF0E1E9787CB523D5E973C1CA0491DD76B2684
      CB3F3B1CAAB75945C1C9500879FBCCA550016A96EAF13A559A70D787998C1B4E
      1D521824E914E53AFAD3752077B700CC2AF87145D4521E3E7CB81665526EDF59
      9D483A4559822B8742DA73F2740BB0BEAE0EDD02800B31EF24AF6E91748AB204
      570E85F7C3EDDCB9337100A14EFD70808BB5CE552549A728D7ADEAA72EA8E33B
      21AC2A0175AE9B4C324519B41B2E24B221C12584419F7605DD5527C914E5E8CF
      B53C8A45824B0087DDD4BDF72DCD14E576B334453624B836B0FB3D497F60D549
      3345993E79DDFFE6AA21C1C5C0B10328DDC222CDE3B721A9DFEDB4479A29CA12
      5C39487031B0DF2D6F689CA65CB74DD2B4539445F1487001183EF7F502A625F4
      308E4E92768AB2280709CE43912D379C908C7AD26E2691D34C51069CF4ACC477
      B148701EA253B98AA49B8B37E9146522C1958304E7E006168AA4EE393C911F09
      CE21FAB8E1A2D1A516129C101D4482F3401F4EFE8B281A09CE03F366792BE551
      D981D6238CD1F3052644FF21C179E0137DF2A404985A40FBD1B871E3ECB88981
      8181DAB6F5886290E03C205CFEF5EB575B51CFD039E66AA2A525FAC82A1F3443
      91EC46AD2245ABEA7B0124380F7C56F6F8F1E3EDC0A37BF7EE799F8B1707848A
      DF632DA2AAEF0590E03C44A721672D7D92E0840F09CE816314103041A7C0D0D0
      50CBEC92A426251F54C9CE6A989498DB82879A88FE45827388FA5E10CD850B17
      EC4882D7AF5FA77A88A03BAC071DE38383839A61D9E748700E685B813050511F
      2D62CE327F32FA0422140897F9285F510F2438213A880427440791E084E820FF
      077C1FF2AAB92C4BFB0000000049454E44AE426082}
  end
  object FunctionYImage: TImage
    Left = 514
    Top = 29
    Width = 215
    Height = 55
    Picture.Data = {
      0954506E67496D61676589504E470D0A1A0A0000000D49484452000000DC0000
      0037080600000067D924C0000000017352474200AECE1CE90000000467414D41
      0000B18F0BFC6105000000097048597300000EC300000EC301C76FA864000008
      114944415478DAED9B4BA84EDF1FC6BF672EB99B5026944B94994B21D7994214
      227706840C882131702913772314B90D28B984DC06A4C8A52813462EA194E1EF
      FF7F563D6FEBECB3F6DEEBDDE73D6BBFE7F77B3E13E7B5DF7D596B3DCF5ADFEF
      77EDB7E39FFF6342882474C87042A44386132221329C100991E18448880C2744
      426438211222C3099110194E8884C87042244486132221329C100991E1844888
      0C2744426438211222C3099110194E8884C87042244486132221325C9BF2ECD9
      33BB79F3A6EDD8B1C3FAF5EBD7B2EF8A7A91E1DA903B77EED8C3870F6DEFDEBD
      D1E77CFCF8D1F6ECD963274E9C90E9DA1819AECDF8F2E58BCD9B37CFDEBC79D3
      F4B967CF9E75FFAE5EBDBAEE66881C7AD470AF5FBFB67DFBF6D9DAB56B6DF6EC
      D951E75CB972C5EEDEBD6B9B366DB2F1E3C7D7DD3FC981697EFFFE6DDBB66D6B
      FA5C9875E2C489F6F5EBD7BA9BD1852A5AA8F3DE653AACAAD35CC3E121274C98
      D0F8FCF4E9539B346992FB1BA258B3664DE358E812086F1E3F7E6CA74E9DB291
      234736DD415BB66CB1F9F3E757125E4A8E1C3962FBF7EFB76FDFBED9D8B163ED
      DAB56BAEBD6C0342C3C18307DBAE5DBB1A6DF9F5EB971D3C78D08900E0F89327
      4FDC794B962CB1AD5BB736FA9AB0CF2F5FBE6C0B172E74F7DDBE7DBB7DF8F0A1
      53FF0E1932A471AD76A18A16D00F972E5DB2EEAE073DA9C32A3A2D5CE138A887
      0F1FEE72C1E9D3A7DBBB77EF82830B71E01C34B46A3E01518E1A35CA8E1D3BE6
      04D68EA07FCE9C3963B76EDDB23E7DFAD8D4A953EDC2850B3660C000B7D21C38
      70C085779CBC6EDFBEED66587EFEF9F3A7BBCE860D1B6CF7EEDD6EA684D0F8B7
      DF17CF9F3F777FC3A49B376FB6BE7DFB06F3BCD0F97552550BAD305C0A1D36AB
      D342C32144193E7C7817C3F1FFFD552FE658B3A0783067CE1CFBFCF9B30D1B36
      AC5BD7EA09B09AD0543E0837162D5AD4492C10108C888161E83766CC18679E99
      336736045164180C6EFFFEFD1BAB5C8876325C2BB550E7BDCB74D88C4E4B7338
      AC64E0C183078DFFC3A0CE9D3B37989C6309BF7EFD7AA5A43F0444ED8763ED44
      55C301AE5A681772AE972F5FBAC1CA0B290157C62211B55348D96A2DD479EF32
      1DC6EAB4D4700C2B11FE60168698B0D45FBC7831F7C6EBD7AF0F96B4B1C4EFDC
      B9D37D87CB3CCAD9EBD6ADB3EFDFBF073B0749E9A3478F6A1934CC92C78F1FB7
      93274FBA1C6DDAB46976EEDCB9C62C86677BFFFEBD1B5870F5EA555BB06081FD
      F9F3C7CDAE08374321A55F18E1AAF5EAD52BB72A858A2610CFE2C58BEDDEBD7B
      EEF38F1F3F6CE5CA95F6F7EFDF4E2B596CD184A1D6DBB76FDD67B4CBCF71B0AF
      07F12064051B376E741AF04D8C71C335D03F007928565D4E28655AC8DE03F92F
      EE81FE427B99DF529E5C4500FAEAC58B174E4B1817F44D763BA4E8DEDC42818E
      FD68817932C7A9191DC6EAB4D470BE58468C186153A64C71897A2826464310CF
      5268D9637820741AC48886229442FE72E8D0A1DCA5989D40C3A7028240320C51
      AC5AB5CA0D6CB66D300B9E1F0307C19D3F7FBE315010084C0351FB62E2B165CB
      96B96B0284801406B705FCBCA3A3A3C3891EC5199899E1288CEEF749CCB6008B
      3CA8B0C1AC1C5F1A9EC2A610F13CCB972F77F93A5761E62D388E6B01F413CC47
      39156981F7E431B619FDC4899CA6F3E5C96783C11836678B4965F7E6B5F19200
      0A57984C3141E1DA304BDE0A55A6C3589D466D0B70C0319B1F3D7A34373FC80E
      5E1E0853478F1E6D03070E749D57F45D36A4EC9A78C658F206825050D9CA6259
      FED42A7A6AE39B794D511BC68D1B6783060DEA944250C09C1838CE7E6ECF6B53
      4E455AE098FAA131DA7CFAF4E986E1F81D5F9ED94881509F5C5D6375884975F2
      E4C9EE7A884EFCD5394B990EA3751A63382C9798BDCA841ADB50CEB2A1FCA76A
      435A099F0F2B39561424C3301FC8AE2A3D055FD78A315DECAB5DCC2DF3FA92C6
      0A55A5216A4C8E3404264D4C0A10FA8A152BBAE494455A60E80B10F6213C0E55
      BAF30C97BD66F6D96275C849142B6B592533B9E1305865B9416C4339F031559D
      3A0C87599EF90D42C5193366B801F5AB89BD9190887DB2A19E4F56D4BC1E73C1
      6C1E58A605EE45323F66C8CCFE4D61385094EB85FA2E89E1F050D984384459EC
      CC8E66DE1353B28D8E8D5B1852E25AA159BEB7C3BECC6E969350A8E8F749D670
      84392974C2A2418C1600F480700ECFE5E7B2DD315CECBDF9DCC887FD10BAA8EF
      7A3C878B7D78523663B0E2B674E952F78065A2AEA34A19321CFAE1C68D1BBDDA
      847939900FC6CF370EC8EEC7425C9F3E7DEA34C6AC66FB72CAD302B63EB2AF59
      21441D3A7468540E5766B8A27B13565951554621A6CC28C9AA94CCDF628B0545
      FB1F98511046C2B87C40C4CE082DF2F28F3AF6E120088449788304212F2B8E7C
      6DAB370361630B866D8199500DC4EA82B652E834975FA564753A5B3E0F551941
      9E16D0BFF7EFDF6FEC178642595629FDB483554A7FC2601E8690D65FA58A74C8
      280B0526569FA16F98189A0C2D2C49F6E1386B91989898B3A1DF29AC06F9AB06
      3A79D6AC59EE4111FB8742CBBADE34F1C35E003122C768C7B75DAAB48D257CE0
      97D849769F0E6DA72101C60EE90572716E6D64BF03425A00AC48B27FF9AE29B6
      5FB8D78B1C9FC7503B60A4451816FBF976767B2574EFEC8403B8A8E0FCD0C49F
      F44D932AF01DC356BCC31653C914ED4B2BB450E7BDCB74D8AC4E7BECE739DD79
      4B9B6F9FF4865F0B8872BAA3853AEF5DA6C32A3A4DF27BB8BC770343FCD77F0F
      F76FA58A16EABC77F2DFC309215A8F0C2744426438211222C3099110194E8884
      C87042244486132221329C100991E18448880C2744426438211222C309911019
      4E8884C87042244486132221329C1009F91F6476CEC54C49BEE5000000004945
      4E44AE426082}
  end
  object NParameterLabel: TLabel
    Left = 24
    Top = 224
    Width = 59
    Height = 13
    Caption = 'Sum limit(n):'
  end
  object AlphaParameterEdit: TEdit
    Left = 80
    Top = 48
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '0.1'
  end
  object BetaParameterEdit: TEdit
    Left = 80
    Top = 112
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '1.0'
  end
  object HParameterEdit: TEdit
    Left = 80
    Top = 176
    Width = 121
    Height = 21
    TabOrder = 2
    Text = '0.1'
  end
  object CalculateButton: TButton
    Left = 544
    Top = 280
    Width = 75
    Height = 25
    Caption = 'Calculate'
    TabOrder = 3
    OnClick = CalculateButtonClick
  end
  object NParameterEdit: TEdit
    Left = 80
    Top = 243
    Width = 121
    Height = 21
    TabOrder = 4
    Text = '10'
  end
  object FunctionOutputGrid: TStringGrid
    Left = 226
    Top = 83
    Width = 261
    Height = 225
    ColCount = 2
    DefaultColWidth = 128
    FixedCols = 0
    RowCount = 9
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 5
  end
  object CalculateRadioGroup: TRadioGroup
    Left = 514
    Top = 169
    Width = 129
    Height = 105
    Caption = 'Configuration:'
    Items.Strings = (
      ' Y(x)'
      ' S(x)'
      ' |Y(x) - S(x)|')
    TabOrder = 6
  end
end
