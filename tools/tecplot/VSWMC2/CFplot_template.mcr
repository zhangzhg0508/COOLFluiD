#!MC 1200
# Created by Tecplot 360 build 12.0.0.3454
$!VarSet |MFBD| = 'RESULTS_DIR'
$!READDATASET  '"|MFBD|/output.plt.bin" '
  READDATAOPTION = NEW
  RESETSTYLE = YES
  INCLUDETEXT = NO
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYNAME
  ASSIGNSTRANDIDS = YES
  INITIALPLOTTYPE = CARTESIAN3D
  VARNAMELIST = '"x0" "x1" "x2" "rho" "u" "v" "w" "Bx" "By" "Bz" "p" "phi"'
$!READDATASET  '"|MFBD|/output.surf.plt.bin" '
  READDATAOPTION = APPEND
  RESETSTYLE = NO
  INCLUDETEXT = NO
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYNAME
  ASSIGNSTRANDIDS = YES
  INITIALPLOTTYPE = CARTESIAN3D
  VARNAMELIST = '"x0" "x1" "x2" "rho" "u" "v" "w" "Bx" "By" "Bz" "p" "phi"'
$!VIEW FIT
$!CREATESLICEZONEFROMPLANE 
  SLICESOURCE = VOLUMEZONES
  FORCEEXTRACTIONTOSINGLEZONE = YES
  COPYCELLCENTEREDVALUES = NO
$!GLOBALTHREED SLICE{NORMAL{Y = 1}}
$!GLOBALTHREED SLICE{NORMAL{Z = 0}}
$!CREATESLICEZONEFROMPLANE 
  SLICESOURCE = VOLUMEZONES
  FORCEEXTRACTIONTOSINGLEZONE = YES
  COPYCELLCENTEREDVALUES = NO
$!FIELDLAYERS USETRANSLUCENCY = NO
$!REDRAWALL 
$!GLOBALCONTOUR 1  VAR = 4
$!CONTOURLEVELS RESETTONICE
  CONTOURGROUP = 1
  APPROXNUMVALUES = 15
$!FIELDLAYERS SHOWCONTOUR = YES
$!REDRAWALL 
$!THREEDVIEW 
  PSIANGLE = 67.7177
  THETAANGLE = -132.005
  ALPHAANGLE = 4.49974
  VIEWERPOSITION
    {
    X = 1748.405705043907
    Y = 1558.768130830779
    Z = 954.4867804107042
    }
$!VIEW PUSH
$!FIELDLAYERS SHOWEDGE = NO
$!REDRAWALL 
$!VIEW ZOOM
  X1 = -49.2651262646
  Y1 = -45.9507962233
  X2 = 66.0759750374
  Y2 = 36.620685315
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!PICK ADDATPOSITION
  X = 5.7802153114
  Y = 3.47239502333
  CONSIDERSTYLE = YES
$!PICK ADDATPOSITION
  X = 4.68426209348
  Y = 3.47239502333
  CONSIDERSTYLE = YES
$!PICK ADDATPOSITION
  X = 7.07543275076
  Y = 6.8067651633
  CONSIDERSTYLE = YES
$!FIELDLAYERS SHOWMESH = YES
$!REDRAWALL 
$!FIELDLAYERS SHOWMESH = NO
$!REDRAWALL 
$!THREEDVIEW 
  PSIANGLE = 66.2136
  THETAANGLE = -129.37
  ALPHAANGLE = 4.04766
  VIEWERPOSITION
    {
    X = 1794.766904669299
    Y = 1468.722125197927
    Z = 1010.49875895462
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 68.3729
  THETAANGLE = -131.663
  ALPHAANGLE = 3.93758
  VIEWERPOSITION
    {
    X = 1761.783372430943
    Y = 1562.88655991465
    Z = 922.9253441241189
    }
$!VIEW PUSH
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.77105748685
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.70001715743
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.64229688977
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.58901664271
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.55793649859
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.49133618975
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.40253577797
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.34481551032
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.32705542796
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.26489513972
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.23381499559
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.18941478971
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.16277466617
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.14501458382
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.12281448087
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.1094944191
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.07841427498
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.07397425439
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.06509421322
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.06065419263
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.05177415145
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.04733413086
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.03401406909
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.03401406909
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.0295740485
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.02513402792
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.02513402792
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.02069400733
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.01625398674
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.01181396615
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.00737394556
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 3.00737394556
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.99849390438
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.98517384262
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.98073382203
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.95409369849
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.93633361614
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.93633361614
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.93633361614
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.93633361614
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.93633361614
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.94077363673
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 2.94077363673
$!VIEW TRANSLATE
  X = -0.138377931555
  Y = -0.466562986003
$!VIEW TRANSLATE
  X = 0.968645520886
  Y = -1.24416796267
$!VIEW TRANSLATE
  X = 0.553511726221
  Y = -0.933125972006
$!VIEW TRANSLATE
  X = 0.27675586311
  Y = 0
$!VIEW TRANSLATE
  X = 0.27675586311
  Y = -0.466562986003
$!VIEW TRANSLATE
  X = 0.27675586311
  Y = 0
$!VIEW TRANSLATE
  X = 0.27675586311
  Y = -0.311041990669
$!VIEW TRANSLATE
  X = 0.138377931555
  Y = -0.466562986003
$!VIEW TRANSLATE
  X = 0.138377931555
  Y = -0.155520995334
$!VIEW TRANSLATE
  X = 0.27675586311
  Y = 0
$!VIEW TRANSLATE
  X = -0.138377931555
  Y = 0
$!VIEW TRANSLATE
  X = -0.138377931555
  Y = 0.466562986003
$!ThreeDAxis XDetail{ShowAxis = Yes}
$!ThreeDAxis YDetail{ShowAxis = Yes}
$!ThreeDAxis ZDetail{ShowAxis = Yes}
$!RedrawAll 
$!View DataFit
  ConsiderBlanking = Yes
$!Pick AddAtPosition
  X = 8.69866444073
  Y = 1.31844741235
  ConsiderStyle = Yes
$!Pick Shift
  X = -6.01001669449
  Y = 0.480801335559
$!Pick AddAtPosition
  X = 7.55008347245
  Y = 6.17988313856
  ConsiderStyle = Yes
$!RedrawAll 
$!Pick AddAtPosition
  X = 6.26794657763
  Y = 5.9929048414
  ConsiderStyle = Yes
$!ThreeDAxis XDetail{TickLabel{TextShape{Height = 8}}}
$!ThreeDAxis YDetail{TickLabel{TextShape{Height = 8}}}
$!ThreeDAxis ZDetail{TickLabel{TextShape{Height = 8}}}
$!RedrawAll 
$!Pick AddAtPosition
  X = 6.76210350584
  Y = 5.8459933222
  ConsiderStyle = Yes
$!ThreeDAxis XDetail{Title{TitleMode = UseText}}
$!ThreeDAxis XDetail{Title{Text = 'x/R_e'}}
$!ThreeDAxis XDetail{Title{TextShape{Height = 10}}}
$!ThreeDAxis YDetail{Title{TitleMode = UseText}}
$!ThreeDAxis YDetail{Title{Text = 'y/R_e'}}
$!ThreeDAxis YDetail{Title{TextShape{Height = 10}}}
$!ThreeDAxis ZDetail{Title{TitleMode = UseText}}
$!ThreeDAxis ZDetail{Title{Text = 'z/R_e'}}
$!ThreeDAxis ZDetail{Title{TextShape{Height = 10}}}
$!RedrawAll
$!View DataFit
  ConsiderBlanking = Yes
$!ThreeDAxis XDetail{Title{Offset = 16}}
$!ThreeDAxis YDetail{Title{Offset = 16}}
$!ThreeDAxis ZDetail{Title{Offset = 16}}
$!RedrawAll
$!GlobalContour 1  Legend{Box{BoxType = Filled}}
$!RedrawAll
$!Pick AddAtPosition
  X = 8.69866444073
  Y = 1.39858096828
  ConsiderStyle = Yes
$!Pick Shift
  X = -0.0534223706177
  Y = 5.36894824708
$!Pick AddAtPosition
  X = 9.01919866444
  Y = 7.7825542571
  ConsiderStyle = Yes
$!VIEW PUSH
$!EXPORTSETUP EXPORTFORMAT = PNG
$!EXPORTSETUP EXPORTREGION = ALLFRAMES
$!EXPORTSETUP IMAGEWIDTH = 722
$!EXPORTSETUP EXPORTFNAME = 'RESULTS_DIR/rho_final.png'
$!EXPORT 
  EXPORTREGION = ALLFRAMES
$!GLOBALCONTOUR 1  VAR = 10
$!CONTOURLEVELS RESETTONICE
  CONTOURGROUP = 1
  APPROXNUMVALUES = 15
$!FIELDLAYERS SHOWCONTOUR = YES
$!REDRAWALL
$!VIEW PUSH
$!EXPORTSETUP EXPORTFORMAT = PNG
$!EXPORTSETUP EXPORTREGION = ALLFRAMES
$!EXPORTSETUP IMAGEWIDTH = 722
$!EXPORTSETUP EXPORTFNAME = 'RESULTS_DIR/Bz_final.png'
$!EXPORT
  EXPORTREGION = ALLFRAMES
$!GLOBALCONTOUR 1  VAR = 11
$!CONTOURLEVELS RESETTONICE
  CONTOURGROUP = 1
  APPROXNUMVALUES = 15
$!FIELDLAYERS SHOWCONTOUR = YES
$!REDRAWALL
$!VIEW PUSH
$!EXPORTSETUP EXPORTFORMAT = PNG
$!EXPORTSETUP EXPORTREGION = ALLFRAMES
$!EXPORTSETUP IMAGEWIDTH = 722
$!EXPORTSETUP EXPORTFNAME = 'RESULTS_DIR/p_final.png'
$!EXPORT
  EXPORTREGION = ALLFRAMES
$!RemoveVar |MFBD|





