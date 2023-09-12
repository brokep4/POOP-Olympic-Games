package projekat;

import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class SysClass {
	
	static {
		System.loadLibrary("DllPOOP2");
	}
	
	////////////////////////////////////////////////
	//C++ PART
	private long pointer; // pointer to C++ System
	private static native long generateFilter(long pointer, String sportName, Integer year, String type, String medal);
	private static native HashMap<String, Integer> _numberOfParticipantsGroupedByCountry(long pointer, long filterPtr);
	private static native HashMap<String, Integer> _numberOfDisciplinesGroupedByOlGames(long pointer, long filterPtr);
	private static native HashMap<String, Double> _averageHeightGroupedByOlGames(long pointer, long filterPtr);
	private static native HashMap<String, Double> _averageWeightGroupedByOlGames(long pointer, long filterPtr);
	private static native long _createObject();
	private static native void _deleteObject(long ptr);
	private static native boolean _loadGroupMode(long pointer, String path);
	private static native boolean _loadIndividualMode(long pointer, String path, int year);
	private static native boolean _loadAthletes(long pointer, String path);
	////////////////////////////////////////////////
	
	public static int getYearFromString(String s)
	{
		Pattern p = Pattern.compile("\\d+");
        Matcher m = p.matcher(s);
        if(!m.find())
        	return 0;
        return Integer.valueOf(m.group(0));
	}
	
	public SysClass() {
		pointer = _createObject();
		System.out.println("Creating SysClass with C++ pointer:" + pointer);
	}
	@Override
	protected void finalize() throws Throwable {
		_deleteObject(pointer);
	}
	
	public HashMap<String, Integer> numberOfParticipantsGroupedByCountry(String sportName, Integer year, String type, String medal)
	{
		return _numberOfParticipantsGroupedByCountry(pointer,generateFilter(pointer,sportName, year, type, medal));
	}
	public HashMap<String, Integer> numberOfDisciplinesGroupedByOlGames(String sportName, Integer year, String type, String medal)
	{
		return _numberOfDisciplinesGroupedByOlGames(pointer,generateFilter(pointer,sportName, year, type, medal));
	}
	public HashMap<String, Double> averageHeightGroupedByOlGames(String sportName, Integer year, String type, String medal)
	{
		return _averageHeightGroupedByOlGames(pointer,generateFilter(pointer,sportName, year, type, medal));
	}
	public HashMap<String, Double> averageWeightGroupedByOlGames(String sportName, Integer year, String type, String medal)
	{
		return _averageWeightGroupedByOlGames(pointer,generateFilter(pointer,sportName, year, type, medal));
	}
	public boolean loadGroupMode(String path)
	{
		return _loadGroupMode(pointer,path);
	}
	public boolean loadIndividualMode(String path, int year)
	{
		return _loadIndividualMode(pointer,path,year);
	}
	public boolean loadAthletes(String path)
	{
		return _loadAthletes(pointer,path);
	}
}
