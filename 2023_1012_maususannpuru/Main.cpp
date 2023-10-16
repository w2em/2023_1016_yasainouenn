# include <Siv3D.hpp>

/// @brief アイテムのボタン
/// @param rect ボタンの領域
/// @param texture ボタンの絵文字
/// @param font 文字描画に使うフォント
/// @param name アイテムの名前
/// @param desc アイテムの説明
/// @param count アイテムの所持数
/// @param enabled ボタンを押せるか
/// @return ボタンが押された場合 true, それ以外の場合は false
bool Button(const Rect& rect, const Texture& texture, const Font& font, const String& name, const String& desc, int32 count, bool enabled)
{
	if (enabled)
	{
		rect.draw(ColorF{ 0.3, 0.5, 0.9, 0.8 });

		rect.drawFrame(2, 2, ColorF{ 0.5, 0.7, 1.0 });

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}
	else
	{
		rect.draw(ColorF{ 0.0, 0.4 });

		rect.drawFrame(2, 2, ColorF{ 0.5 });
	}

	texture.scaled(0.5).drawAt(rect.x + 50, rect.y + 50);

	font(name).draw(30, rect.x + 100, rect.y + 15, Palette::White);

	font(desc).draw(18, rect.x + 102, rect.y + 60, Palette::White);

	font(count).draw(50, Arg::rightCenter((rect.x + rect.w - 20), (rect.y + 50)), Palette::White);

	return (enabled && rect.leftClicked());
}

void Main()
{
	const Texture texture1{ U"🥕"_emoji };
	const Texture texture2{ U"🥬"_emoji };
	const Texture texture3{ U"🍅"_emoji };

	const Texture farmEmoji{ U"🌱"_emoji };
	const Texture factoryEmoji{ U"💊"_emoji };
	const Texture robottoEmoji{ U"🤖"_emoji };

	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	const Circle cookieCircle1{ 100, 300, 100 };
	const Circle cookieCircle2{ 100, 500, 100 };
	const Circle cookieCircle3{ 300, 500, 100 };

	double cookieScale1 = 1.5;
	double cookieScale2 = 1.5;
	double cookieScale3 = 1.5;

	double num = 0;

	int32 farmCount = 0;

	int32 factoryCount = 0;
	int32 robottoCount = 0;

	int32 farmCost = 10;

	int32 factoryCost = 100;
	int32 robottoCost = 1000;

	// ゲームの経過時間の蓄積
	double accumulatedTime = 0.0;

	while (System::Update())
	{
		const int32 cps = (farmCount + factoryCount * 10 + robottoCount * 100);

		// ゲームの経過時間を加算する
		accumulatedTime += Scene::DeltaTime();

		// 0.1 秒以上蓄積していたら
		if (0.1 <= accumulatedTime)
		{
			accumulatedTime -= 0.1;

			num += (cps * 0.1);
		}

		farmCost = 10 + (farmCount * 10);
		factoryCost = 100 + (factoryCount * 100);
		robottoCost = 1000 + (robottoCount * 1000);

		if (cookieCircle1.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
		if (cookieCircle2.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
		if (cookieCircle3.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (cookieCircle1.leftClicked()||cookieCircle1.rightClicked())
		{
			cookieScale1 = 1.3;
			++num;
		}
		if (cookieCircle2.leftClicked()||cookieCircle2.rightClicked())
		{
			cookieScale2 = 1.3;
			num += 2;
		}
		if (cookieCircle3.leftClicked()||cookieCircle3.rightClicked())
		{
			cookieScale3 = 1.3;
			num += 3;
		}

		cookieScale1 += Scene::DeltaTime();
		cookieScale2 += Scene::DeltaTime();
		cookieScale3 += Scene::DeltaTime();

		if (1.5 < cookieScale1)
		{
			cookieScale1 = 1.5;
		}
		if (1.5 < cookieScale2)
		{
			cookieScale2 = 1.5;
		}
		if (1.5 < cookieScale3)
		{
			cookieScale3 = 1.5;
		}

		// 背景を描く
		Rect{ 0, 0, 800, 600 }.draw(Arg::top = ColorF{ 0.5, 0.5, 0.2 }, Arg::bottom = ColorF{ 0.2, 0.5, 0.5 });

		font(U"{:.0f}"_fmt(num)).drawAt(60, 170, 100);

		font(U"毎秒: {}"_fmt(cps)).drawAt(24, 170, 160);

		texture1.scaled(cookieScale1).drawAt(cookieCircle1.center);
		texture2.scaled(cookieScale2).drawAt(cookieCircle2.center);
		texture3.scaled(cookieScale3).drawAt(cookieCircle3.center);

		if (Button(Rect{ 340, 20, 420, 100 }, farmEmoji, font, U"野菜の種", U"C{} / 1 CPS"_fmt(farmCost), farmCount, (farmCost <= num)))
		{
			num -= farmCost;
			++farmCount;
		}
		if (Button(Rect{ 340, 120, 420, 100 }, factoryEmoji, font, U"野菜の農薬", U"C{} / 10 CPS"_fmt(factoryCost), factoryCount, (factoryCost <= num)))
		{
			num -= factoryCost;
			++factoryCount;
		}
		if (Button(Rect{ 340, 220, 420, 100 }, robottoEmoji, font, U"野菜の自動農園", U"C{} / 100 CPS"_fmt(robottoCost), robottoCount, (robottoCost <= num)))
		{
			num -= robottoCost;
			++robottoCount;
		}
	}
}
