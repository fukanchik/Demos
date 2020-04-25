/*
https://stackoverflow.com/questions/4042817/java-calendar-problem-why-are-these-two-dates-not-equal
*/
import java.util.Calendar;

public class CalendarEquality
{
public static void main(String...args)
{
Calendar c = Calendar.getInstance();
c.set(Calendar.YEAR, 2011);
c.set(Calendar.MONTH, 11);
c.set(Calendar.DAY_OF_MONTH, 4);

try { Thread.sleep(10); } catch(Exception e){}

Calendar d = Calendar.getInstance();
d.set(Calendar.YEAR, 2011);
d.set(Calendar.MONTH, 11);
d.set(Calendar.DAY_OF_MONTH, 4);

System.out.println(c.equals(d));
}
}
