const char*RULES[3] = {"�� ������ �������� �������� �������. \
���������� �������� ������� �� ������� ����������, \
��������� �� ����. �� ���� ��������� ��� ������ \
���������� ������ ���������� ������ ���� ������ \
����������� - � ����� �� ��������� 25 ������.",

"�� ������ �������� ���� �������������� �����������. \
������������ �������� � ������� ��� ������ ����, \
�������� ��� ������ ���������. ������ ��������� \
������������ ��������� �������� 20 ������. �� \
�������, ��� �� ����������� � ��� ����� 1 ������! \
� ��� ������ �������� ����� ������������ ������ \
���� ���.",

"����� ���� ������� � 16-� ��������. \
�� ������ ������� ����� 8 �� ���. \
�� 12-� �������� ���������� ������, ���������� \
������� ������� ����� �������� ��� �����, ��������� \
�� ��������������� ������. ��� � ������ �������, \
�� ������ \"?\", ���������� ��� ������ �� +15 ������ \
� ���� \"����\", ����� �� �������, �� ������� ��� \
���� �� ������ ������� � ����������� ���."};
  Graphics::TBitmap *lvlpic = new Graphics::TBitmap;
  lvlpic->Width = 640;
  lvlpic->Height = 480;
  lvlpic->Canvas->Font->Color = clYellow;
  lvlpic->Canvas->Font->Size = 16;
  lvlpic->Canvas->Font->Name = "Georgia";
  lvlpic->Canvas->Brush->Color = clBlack;
  lvlpic->Canvas->FillRect(Canvas->ClipRect);
  static int i = 0;
  RECT r = {30, 240, 610, 470};
  DrawText(lvlpic->Canvas->Handle, RULES[i], strlen(RULES[i]), &r,
    DT_WORDBREAK|DT_CENTER);

  i++;
  AnsiString s = "������� " + IntToStr(i);
  if (i == 3) i = 0;
  lvlpic->Canvas->Font->Size = 50;
  lvlpic->Canvas->Font->Color = clAqua;
  r.top = 140;
  DrawText(lvlpic->Canvas->Handle, s.c_str(), s.Length(), &r,
    DT_CENTER);
  Canvas->Draw(0, 0, lvlpic);
  delete lvlpic;
