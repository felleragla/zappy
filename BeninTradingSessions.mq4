#property strict
#property indicator_chart_window

// Indicator: Trading sessions for Benin timezone (GMT+1)
// Draws Asian, European, American sessions and their overlap on the chart.
// Times are converted from Benin local time to broker server time using an input offset.

input color AsianColor   = clrAliceBlue;   // Asian session color
input color EuropeColor  = clrPaleGreen;   // European session color
input color USColor      = clrMistyRose;   // American session color
input color OverlapColor = clrGold;        // Europe/US overlap color
input int   BrokerGMTOffset = 0;           // Broker server offset from GMT (e.g., GMT+2 -> 2)

const int BeninOffset = 1; // GMT+1

int OnInit()
{
    IndicatorSetString(INDICATOR_SHORTNAME, "Benin Trading Sessions");
    return(INIT_SUCCEEDED);
}

void OnDeinit(const int reason)
{
    // remove session rectangles
    ObjectsDeleteAll(0, "Sess_");
}

int OnCalculate(const int rates_total,
                const int prev_calculated,
                const datetime &time[],
                const double &open[],
                const double &high[],
                const double &low[],
                const double &close[],
                const long &tick_volume[],
                const long &volume[],
                const int &spread[])
{
    DrawAllSessions();
    return(rates_total);
}

// Draw session rectangles for a range of days
void DrawAllSessions()
{
    // Look back 10 days and one day ahead
    datetime from = iTime(NULL, PERIOD_D1, 10);
    datetime to   = iTime(NULL, PERIOD_D1, 0) + 86400;
    for (datetime day = from; day <= to; day += 86400)
    {
        DrawSession(day, 0, 10,  "Asian",   AsianColor);
        DrawSession(day, 8, 16,  "Europe",  EuropeColor);
        DrawSession(day, 13, 23, "US",      USColor);
        DrawSession(day, 14, 17, "Overlap", OverlapColor);
    }
}

// Create or update a session rectangle
void DrawSession(datetime day, int startHour, int endHour, string label, color col)
{
    datetime start = SessionTime(day, startHour);
    datetime end   = SessionTime(day, endHour);
    string name = "Sess_" + label + "_" + TimeToString(day, TIME_DATE);
    if (ObjectFind(0, name) == -1)
        ObjectCreate(0, name, OBJ_RECTANGLE, 0, start, 0, end, 0);
    ObjectSetInteger(0, name, OBJPROP_BACK, true);
    ObjectSetInteger(0, name, OBJPROP_COLOR, col);
    ObjectSetInteger(0, name, OBJPROP_STYLE, STYLE_SOLID);
    ObjectSetInteger(0, name, OBJPROP_WIDTH, 1);
    ObjectSetInteger(0, name, OBJPROP_TIME1, start);
    ObjectSetInteger(0, name, OBJPROP_TIME2, end);
}

// Convert a Benin local hour to broker server time
datetime SessionTime(datetime day, int hour)
{
    int delta = BeninOffset - BrokerGMTOffset;
    return day + (hour - delta) * 3600;
}
