
//---------------------------------------------------------------------------
void TAnalyserBaseFrame::LoadBaseInits(ASS fileName)
{
 TIniFile *iniFile=new TIniFile(fileName);

 _userMinFreq=iniFile->ReadInteger("Band","UserMinFreq",50000);
 _userMinFreq=iniFile->ReadInteger("Band","UserNaxFreq",90000);
 BandsRadioGroup->ItemIndex=iniFile->ReadInteger("Band","Index",0);

 //FreqPageControl->TabIndex=iniFile->ReadInteger("Freq","TabIndex",0);
 //FreqPageControl->ActivePageIndex=iniFile->ReadInteger("Freq","TabIndex",0);
 FreqSetComboBox->ItemIndex=iniFile->ReadInteger("Freq","TabIndex",0);
 FreqSetComboBoxChange(this);
 RatioComboBox->ItemIndex=iniFile->ReadInteger("Freq","RatioIndex",RatioComboBox->ItemIndex);
 this->RatioComboBoxChange(this);
 LeftScrollBar->Position=iniFile->ReadInteger("Freq","Left",70000);
 RightScrollBar->Position=iniFile->ReadInteger("Freq","Right",90000);

 //_userQualStep=iniFile->ReadInteger("Qual","Step",20);
 //_userQualCount=iniFile->ReadInteger("Qual","Count",20);
 //QualRadioGroup->ItemIndex=iniFile->ReadInteger("Qual","Index",1);
 //this->QualRadioGroupClick(QualRadioGroup);

 BeamWidthComboBox->ItemIndex=iniFile->ReadInteger("Beam","Width",BeamWidthComboBox->ItemIndex);
 BeamFadingUpDown->Position=iniFile->ReadInteger("Beam","Fading",BeamFadingUpDown->Position);
 this->BeamFadingEditChange(this);
 BeamCheckBox->Checked=iniFile->ReadBool("Beam","Single",BeamCheckBox->Checked);
 BeamRefreshCheckBox->Checked=iniFile->ReadBool("Beam","Refresh",BeamRefreshCheckBox->Checked);
 BeamShadowCheckBox->Checked=iniFile->ReadBool("Beam","Shadow",BeamShadowCheckBox->Checked);
 BeamShadowCheckBoxClick(this);
 BeamWidthComboBoxChange(this);

 //WorkContRadioButton->Checked=iniFile->ReadBool("Work","Cont",true);
// WorkIntervalRadioButton->Checked=iniFile->ReadBool("Work","Int",true);
 //WorkOnceRadioButton->Checked=iniFile->ReadBool("Work","Once",true);
 //WorkIntervalUpDown->Position=iniFile->ReadInteger("Work","Interval",1);
 //IntervalEditChange(this);

 LevelAutoFitCheckBox->Checked=iniFile->ReadBool("Level","AutoFit",LevelAutoFitCheckBox->Checked);
 LevelAmpScrollBar->Position=iniFile->ReadInteger("Level","Amp",80);
 LevelCenterScrollBar->Position=iniFile->ReadInteger("Level","Center",0);

 FonColorComboBox->ItemIndex=iniFile->ReadInteger("Colors","FonColor",FonColorComboBox->ItemIndex);
 FonGradientCheckBox->Checked=iniFile->ReadBool("Colors","FonGradient",FonGradientCheckBox->Checked);
 this->FonRadioGroupClick(this);

 BeamColorComboBox->ItemIndex=iniFile->ReadInteger("Colors","BeamColor",BeamColorComboBox->ItemIndex);
 BeamColorCheckBox->Checked=iniFile->ReadBool("Colors","BeamInverse",BeamColorCheckBox->Checked);
 this->BeamColorRadioGroupClick(this);

 GridColorComboBox->ItemIndex=iniFile->ReadInteger("Colors","GridColor",GridColorComboBox->ItemIndex);
 GridColorAdaptCheckBox->Checked=iniFile->ReadBool("Colors","GridColorAdapt",GridColorAdaptCheckBox->Checked);
 GridColorNoCheckBox->Checked=iniFile->ReadBool("Colors","GridColorNo",GridColorNoCheckBox->Checked);
 GridColorSplashCheckBox->Checked=iniFile->ReadBool("Colors","GridSplash",GridColorSplashCheckBox->Checked);
 this->GridColorAdaptCheckBoxClick(this);
 this->GridColorNoCheckBoxClick(this);   
 this->GridColorSplashCheckBoxClick(this);

 LegendXColorBox->ItemIndex=iniFile->ReadInteger("Colors","LegendXColor",LegendXColorBox->ItemIndex);
 LegendYColorBox->ItemIndex=iniFile->ReadInteger("Colors","LegendYColor",LegendYColorBox->ItemIndex);
 LegendColorCheckBox->Checked=iniFile->ReadBool("Colors","LegendColorAdapt",LegendColorCheckBox->Checked);
 this->LegendColorCheckBoxClick(this);

 // FreqPlan
 FreqPlanNameEdit->Caption=iniFile->ReadString("FreqPlan","Name","");
 this->FreqPlanAutoLoadMenuItem->Checked=iniFile->ReadBool("FreqPlan","AutoLoad",FreqPlanAutoLoadMenuItem->Checked);
 this->FreqPlanAutoSaveMenuItem->Checked=iniFile->ReadBool("FreqPlan","AutoSave",FreqPlanAutoSaveMenuItem->Checked);

 FreqPlanLineWidthComboBox->ItemIndex=iniFile->ReadBool("FreqPlan","LineWidth",FreqPlanLineWidthComboBox->ItemIndex);
 FreqPlanLineColorBox->Selected=iniFile->ReadInteger("FreqPlan","LineColor",FreqPlanLineColorBox->Selected);
 FreqPlanNameColorBox->Selected=iniFile->ReadInteger("FreqPlan","NameColor",FreqPlanNameColorBox->Selected);

 FreqPlanLineColorBoxChange(this);
 FreqPlanNameColorBoxChange(this);
 FreqPlanLineWidthComboBoxChange(this);



 delete iniFile;

 if(this->FreqPlanAutoLoadMenuItem->Checked==true)
  //FreqPlanMenuItemClick(FreqPlanLoadMenuItem);
  LoadFreqPlan(FreqPlanNameEdit->Caption);

 LoadInits(fileName);
}
//---------------------------------------------------------------------------
void TAnalyserBaseFrame::SaveBaseInits(ASS fileName)
{
 TIniFile *iniFile=new TIniFile(fileName);

 iniFile->WriteInteger("Band","UserMinFreq",_userMinFreq);
 iniFile->WriteInteger("Band","UserNaxFreq",_userMinFreq);
 iniFile->WriteInteger("Band","Index",BandsRadioGroup->ItemIndex);


 iniFile->WriteInteger("Freq","TabIndex",FreqSetComboBox->ItemIndex);
// iniFile->WriteInteger("Freq","TabIndex",FreqPageControl->TabIndex);
 iniFile->WriteInteger("Freq","RatioIndex",RatioComboBox->ItemIndex);
 iniFile->WriteInteger("Freq","Left",LeftScrollBar->Position);
 iniFile->WriteInteger("Freq","Right",RightScrollBar->Position);

 //iniFile->WriteInteger("Qual","Step",_userQualStep);
// iniFile->WriteInteger("Qual","Count",_userQualCount);
// iniFile->WriteInteger("Qual","Index", QualRadioGroup->ItemIndex);
// iniFile->WriteInteger("Qual","Step",StepScrollBar->Position);

 iniFile->WriteInteger("Beam","Width",BeamWidthComboBox->ItemIndex);
 iniFile->WriteInteger("Beam","Fading",BeamFadingUpDown->Position);
 iniFile->WriteBool("Beam","Single",BeamCheckBox->Checked);
 iniFile->WriteBool("Beam","Shadow",BeamShadowCheckBox->Checked); 
 iniFile->WriteBool("Beam","Refresh",BeamRefreshCheckBox->Checked);

 //iniFile->WriteBool("Work","Cont",WorkContRadioButton->Checked);
// iniFile->WriteBool("Work","Int",WorkIntervalRadioButton->Checked);
 //iniFile->WriteBool("Work","Once",WorkOnceRadioButton->Checked);
 //iniFile->WriteInteger("Work","Interval",WorkIntervalUpDown->Position);

 iniFile->WriteBool("Level","AutoFit",LevelAutoFitCheckBox->Checked);
 iniFile->WriteInteger("Level","Amp",LevelAmpScrollBar->Position);
 iniFile->WriteInteger("Level","Center",LevelCenterScrollBar->Position);  

 iniFile->WriteInteger("Colors","FonColor",FonColorComboBox->ItemIndex);
 iniFile->WriteBool("Colors","FonGradient",FonGradientCheckBox->Checked);

 iniFile->WriteInteger("Colors","BeamColor",BeamColorComboBox->ItemIndex);
 iniFile->WriteBool("Colors","BeamInverse",BeamColorCheckBox->Checked);

 iniFile->WriteInteger("Colors","GridColor",GridColorComboBox->ItemIndex);
 iniFile->WriteBool("Colors","GridColorAdapt",GridColorAdaptCheckBox->Checked);
 iniFile->WriteBool("Colors","GridColorNo",GridColorNoCheckBox->Checked); 
 iniFile->WriteBool("Colors","GridSplash",GridColorSplashCheckBox->Checked);

 iniFile->WriteInteger("Colors","LegendXColor",LegendXColorBox->ItemIndex); 
 iniFile->WriteInteger("Colors","LegendYColor",LegendYColorBox->ItemIndex);
 iniFile->WriteBool("Colors","LegendColorAdapt",LegendColorCheckBox->Checked);
 // FreqPlan
 iniFile->WriteString("FreqPlan","Name",FreqPlanNameEdit->Caption);
 iniFile->WriteBool("FreqPlan","AutoLoad",FreqPlanAutoLoadMenuItem->Checked);
 iniFile->WriteBool("FreqPlan","AutoSave",FreqPlanAutoSaveMenuItem->Checked);

 iniFile->WriteBool("FreqPlan","LineWidth",FreqPlanLineWidthComboBox->ItemIndex);
 iniFile->WriteInteger("FreqPlan","LineColor",FreqPlanLineColorBox->Selected);
 iniFile->WriteInteger("FreqPlan","NameColor",FreqPlanNameColorBox->Selected);

 delete iniFile;

 if(this->FreqPlanAutoSaveMenuItem->Checked==true)
  _bands->BandsSave(FreqPlanNameEdit->Caption);

 SaveInits(fileName);
}

//---------------------------------------------------------------------------