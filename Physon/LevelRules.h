const char*RULES[3] = {"Вы должны показать быстроту реакции. \
Необходимо защитить корабль от опасных метеоритов, \
несущихся на него. За одну отведённую Вам минуту \
количество сбитых метеоритов должно быть больше \
пропущенных - и тогда Вы получаете 25 баллов.",

"Вы должны показать свои математические способности. \
Перетаскивая карточки с числами при помощи мыши, \
соберите два верных равенства. Каждое правильно \
составленное равенство приносит 20 баллов. Но \
помните, что на размышление у Вас всего 1 минута! \
И что каждую карточку можно использовать только \
один раз.",

"Перед Вами таблица с 16-ю ячейками. \
Вы можете открыть ровно 8 из них. \
За 12-ю ячейками скрываются задачи, правильное \
решение которых может принести Вам сумму, указанную \
на соответствующей ячейке. Ещё в четырёх клетках, \
за знаком \"?\", скрываются три бонуса по +15 баллов \
и одна \"мина\", попав на которую, Вы теряете все \
очки за третий уровень и оканчиваете его."};
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
  AnsiString s = "Уровень " + IntToStr(i);
  if (i == 3) i = 0;
  lvlpic->Canvas->Font->Size = 50;
  lvlpic->Canvas->Font->Color = clAqua;
  r.top = 140;
  DrawText(lvlpic->Canvas->Handle, s.c_str(), s.Length(), &r,
    DT_CENTER);
  Canvas->Draw(0, 0, lvlpic);
  delete lvlpic;
