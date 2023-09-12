package projekat;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

public class PieChart extends Graph {
	Map<String, Integer> dataMap;
	List<Entry<String, Integer>> dataList;
	int showCnt=4;
	public PieChart(Map<String, Integer> dataMap, int showCnt) {
		// TODO Auto-generated constructor stub
		this.dataMap = dataMap;
		this.showCnt = showCnt;
		makeList();
	}
	public void setDataMap(Map<String, Integer> dataMap)
	{
		this.dataMap = dataMap;
		makeList();
	}
	public void setShowCnt(int cnt)
	{
		showCnt = cnt;
	}
	
	public int getCircleRadius()
	{
		return (int)Math.min(getWidth()*0.8,getHeight()*0.80) / 2;
	}
	public void makeList()
	{
		dataList = new ArrayList<>(dataMap.entrySet());
		dataList.sort(Entry.comparingByValue());
		Collections.reverse(dataList);
	}
	
	private void drawHelp(Graphics g, String text, int angle, int offset)
	{
		Color c = new Color((int)(Math.random() * 0x1000000));
		g.setColor(c);
		g.fillArc(getWidth()/2 - getCircleRadius(), getHeight()/2 - getCircleRadius(), getCircleRadius()*2, getCircleRadius()*2, angle, offset);
		int midAngle = angle + offset/2;
		int xCenter = getWidth()/2;
		int yCenter = getHeight()/2;
		int r = getCircleRadius();
		int xLabel = (int)(r * Math.cos(midAngle / 180.0 * Math.PI)) + xCenter;
		int yLabel = yCenter - (int)(r * Math.sin(midAngle / 180.0 * Math.PI));
		g.setColor(Color.pink);
		g.drawLine(xCenter, yCenter, xLabel,yLabel);
		
		int width = g.getFontMetrics().stringWidth(text);
		int height = g.getFontMetrics().getAscent();
		
		if(midAngle >= 0 && midAngle <= 180)yLabel-=height;//-=20;
		else yLabel +=height;//+= 20;
		if(midAngle >= 90 && midAngle <= 270)xLabel -= width;
		else xLabel += 20;
		
		g.drawString(text, xLabel, yLabel);
	}
	
	
	@Override
	public void paint(Graphics g) {
		super.paint(g);
		int totalCount = 0;
		for(Integer val : dataMap.values())
		{
			totalCount += val;
		}
		int angle = 0;
		int offset;
		g.drawOval(getWidth()/2 - getCircleRadius(), getHeight()/2 - getCircleRadius(), getCircleRadius()*2, getCircleRadius()*2);
		
		int showLeft = showCnt;
		for (Map.Entry<String, Integer> pair : dataList)//for (Map.Entry<String, Integer> pair : dataMap.entrySet())
		{
			offset = (int)(360 * pair.getValue() / totalCount);
			/*
			offset = (int)(360 * pair.getValue() / totalCount);
			Color c = new Color((int)(Math.random() * 0x1000000));
			g.setColor(c);
			g.fillArc(getWidth()/2 - getCircleRadius(), getHeight()/2 - getCircleRadius(), getCircleRadius()*2, getCircleRadius()*2, angle, offset);
			int midAngle = angle + offset/2;
			int xCenter = getWidth()/2;
			int yCenter = getHeight()/2;
			int r = getCircleRadius();
			int xLabel = (int)(r * Math.cos(midAngle / 180.0 * Math.PI)) + xCenter;
			int yLabel = yCenter - (int)(r * Math.sin(midAngle / 180.0 * Math.PI));
			g.setColor(Color.pink);
			g.drawLine(xCenter, yCenter, xLabel,yLabel);
			
			if(midAngle >= 0 && midAngle <= 180)yLabel-=20;
			else yLabel += 20;
			if(midAngle >= 90 && midAngle <= 270)xLabel -= 20;
			else xLabel += 20;
			
			//g.drawLine(xCenter, yCenter, xLabel + xCenter, yLabel + yCenter);
			//g.drawString(xLabel + ", " + yLabel + " -> " + angle + " - " + offset, xLabel, yLabel);
			g.drawString(pair.getKey(), xLabel, yLabel);
			*/
			if(showLeft == 0)break;
			showLeft--;
			drawHelp(g, pair.getKey(), angle, offset);
			angle += offset;
		}
		if(angle < 360)
		{
			drawHelp(g, "Other", angle, 360-angle);
		}
	}
}
