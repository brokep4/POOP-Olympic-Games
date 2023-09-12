package projekat;

import java.awt.Color;
import java.awt.Graphics;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;


class XYEntry<T1, T2>
{
	//T1-x
	//T2-y
	private T1 xval;
	private T2 yval;
	private Color dotColor;
	private int radius;
	public XYEntry(T1 x, T2 y, Color c, int radius) {
		xval = x;
		yval = y;
		dotColor = c;
		this.radius = radius;
	}
	public XYEntry(T1 x, T2 y, Color c) {
		this(x, y, c, 5);
	}
	public T1 getXVal() {return xval;}
	public T2 getYVal() {return yval;}
	public double getXValToDouble() {
		if(xval instanceof Integer)
		{
			return Double.valueOf((Integer)xval);
		}
		return (double) xval;
	}
	public double getYValToDouble() {
		if(yval instanceof Integer)
		{
			return Double.valueOf((Integer)yval);
		}
		return (double) yval;
	}
	public int getRadius() {return radius;}
	public Color getColor() {return dotColor;}
};

public class XYGraph<T1, T2> extends Graph {
	private ArrayList<XYEntry<T1,T2>> pointsArrayList = new ArrayList<>();
	private int numberOfXPositions;
	private int numberOfYPositions;
	private T1 opsegMin, opsegMax;
	public XYGraph(int numberOfXPositions, int numberOfYPositions, T1 opsegMin, T1 opsegMax) {
		if(numberOfXPositions < 2)numberOfXPositions = 7;
		if(numberOfYPositions < 2)numberOfYPositions = 6;
		this.numberOfXPositions = numberOfXPositions;
		this.numberOfYPositions = numberOfYPositions;
		this.opsegMin = opsegMin;
		this.opsegMax = opsegMax;
		
		//setBackground(Color.RED);
	}
	public void addPoint(T1 x, T2 y, Color c)
	{
		XYEntry<T1,T2> point = new XYEntry<T1,T2>(x, y, c);
		pointsArrayList.add(point);
	}
	public void addPoint(T1 x, T2 y, Color c, int radius)
	{
		XYEntry<T1,T2> point = new XYEntry<T1,T2>(x, y, c, radius);
		pointsArrayList.add(point);
	}
	
	private int xMargin()
	{
		return 40;
	}
	private int yMargin()
	{
		return 40;
	}
	
	private int getPlotWidth()
	{
		return getWidth() - xMargin() - 20;
	}
	private int getPlotHeight()
	{
		return getHeight() - yMargin();
	}
	private int getUpperX()
	{
		return xMargin();
	}
	private int getUpperY()
	{
		return 0;
	}
	private int leaveSpaceX() //how much space right should be unoccupied so that graph looks nice
	{
		return 20;
	}
	private int leaveSpaceY() //same for Y
	{
		return 20;
	}
	private int getSizeOfPodeok()
	{
		return 10;
	}
	
	private String formatDouble(double d)
	{
		DecimalFormat format = new DecimalFormat("#.##");
		return format.format(d);
	}
	
	@Override
	public void paint(Graphics g) {
		/*
		super.paint(g);
		g.setColor(Color.black);
		g.drawRect(getUpperX(), getUpperY(), getPlotWidth(), getPlotHeight());
		if(pointsArrayList.size() == 0)return;
		T1 tst1 = pointsArrayList.get(0).getXVal();
		T2 tst2 = pointsArrayList.get(0).getYVal();
		System.out.println("I am here");
		if((tst1 instanceof Double || tst1 instanceof Integer) && (tst2 instanceof Double || tst2 instanceof Integer))
		{
			double minX = pointsArrayList.get(0).getXValToDouble(),maxX = minX,minY = pointsArrayList.get(0).getYValToDouble(),maxY = minY;
			for(XYEntry<T1,T2> entry : pointsArrayList)
			{
				double x = entry.getXValToDouble();
				double y = entry.getYValToDouble();
				if(x < minX) minX = x;
				if(x > maxX) maxX = x;
				if(y < minY) minY = y;
				if(y > maxY) maxY = y;
			}
			double diffX = (maxX - minX) / (numberOfXPositions - 1);
			double diffY = (maxY - minY) / (numberOfYPositions - 1);
			double velicinaPodeokaX = (getPlotWidth() - leaveSpaceX()) / numberOfXPositions;
			double velicinaPodeokaY = (getPlotHeight() - leaveSpaceY()) / numberOfYPositions;
			for(XYEntry<T1,T2> entry : pointsArrayList)
			{
				double x = entry.getXValToDouble();
				double y = entry.getYValToDouble();
				int podeokX = (int)((x-minX)/diffX) + 1;
				double realXPosition = podeokX * velicinaPodeokaX + velicinaPodeokaX * ((podeokX) * diffX - (x-minX)) / diffX;
				int podeokY = (int)((y-minY)/diffY) + 1;
				double realYPosition = podeokY * velicinaPodeokaY + velicinaPodeokaY * ((podeokY) * diffY - (y-minY)) / diffY;
				g.setColor(entry.getColor());
				g.fillOval((int)realXPosition + getUpperX(), getUpperY() + getPlotHeight() - (int)realYPosition, 2*entry.getRadius(), 2*entry.getRadius());
			}
		}
		*/
		super.paint(g);
		g.setColor(Color.black);
		g.drawRect(getUpperX(), getUpperY(), getPlotWidth(), getPlotHeight());
		if(pointsArrayList.size() == 0)return;
		T1 tst1 = pointsArrayList.get(0).getXVal();
		T2 tst2 = pointsArrayList.get(0).getYVal();
		System.out.println("I am here");
		if((tst1 instanceof Double || tst1 instanceof Integer) && (tst2 instanceof Double || tst2 instanceof Integer))
		{
			boolean isset=false;
			double minX = /*pointsArrayList.get(0).getXValToDouble()*/-1,maxX = minX,minY = /*pointsArrayList.get(0).getYValToDouble()*/-1,maxY = minY;
			ArrayList<T1> t1List = new ArrayList<>();
			ArrayList<T2> t2List = new ArrayList<>();
			for(XYEntry<T1,T2> entry : pointsArrayList)
			{
				double uporediMin, uporediMax;
				if(tst1 instanceof Double)
				{
					uporediMin = (Double)opsegMin;
					uporediMax = (Double)opsegMax;
				}
				else 
				{
					//X osa je int
					uporediMin = (Integer)opsegMin;
					uporediMax = (Integer)opsegMax;
				}
				double x = entry.getXValToDouble();
				double y = entry.getYValToDouble();
				if(x < uporediMin || x > uporediMax)continue;
				if(!isset) {minX=maxX=x;minY=maxY=y;isset=true;}
				if(x < minX) minX = x;
				if(x > maxX) maxX = x;
				if(y < minY) minY = y;
				if(y > maxY) maxY = y;
				int postoji1=0;
				int postoji2=0;
				for(T1 en : t1List)
				{
					if(en.equals(entry.getXVal()))postoji1=1;
				}
				for(T2 en : t2List)
				{
					if(en.equals(entry.getYVal()))postoji2=1;
				}
				if(postoji1 == 0)t1List.add(entry.getXVal());
				if(postoji2 == 0)t2List.add(entry.getYVal());
			}
			System.out.println("Sizes: " + t1List.size() + ", " + t2List.size());
			for(T1 t : t1List)
			{
				System.out.println(t);
			}
			if(t1List.size() < numberOfXPositions)numberOfXPositions = t1List.size();
			if(t2List.size() < numberOfYPositions)numberOfYPositions = t2List.size();
			if(numberOfXPositions < 2)numberOfXPositions = 2;
			if(numberOfYPositions < 2)numberOfYPositions = 2;
			double diffX = (maxX - minX) / (numberOfXPositions - 1);
			double diffY = (maxY - minY) / (numberOfYPositions - 1);
			double velicinaPodeokaX = (getPlotWidth() - 2*leaveSpaceX()) / (numberOfXPositions - 1);
			double velicinaPodeokaY = (getPlotHeight() - 2*leaveSpaceY()) / (numberOfYPositions - 1);
			for(XYEntry<T1,T2> entry : pointsArrayList)
			{
				double uporediMin, uporediMax;
				if(tst1 instanceof Double)
				{
					uporediMin = (Double)opsegMin;
					uporediMax = (Double)opsegMax;
				}
				else 
				{
					//X osa je int
					uporediMin = (Integer)opsegMin;
					uporediMax = (Integer)opsegMax;
				}
				
				
				double x = entry.getXValToDouble();
				double y = entry.getYValToDouble();
				
				if(x < uporediMin || x > uporediMax)continue;
				
				int podeokX = (int)((x-minX)/diffX);// + 1;
				//double realXPosition = podeokX * velicinaPodeokaX + velicinaPodeokaX * ((podeokX + 1) * diffX - (x-minX)) / diffX;
				double realXPosition = podeokX * velicinaPodeokaX + velicinaPodeokaX *  ((x-minX) - (podeokX) * diffX) / diffX;
				int podeokY = (int)((y-minY)/diffY);// + 1;
				//double realYPosition = podeokY * velicinaPodeokaY + velicinaPodeokaY * ((podeokY + 1) * diffY - (y-minY)) / diffY;
				double realYPosition = podeokY * velicinaPodeokaY + velicinaPodeokaY *  ((y-minY) - (podeokY) * diffY) / diffY;
				g.setColor(entry.getColor());
				g.fillOval((int)realXPosition + getUpperX() + leaveSpaceX() - entry.getRadius(), -leaveSpaceY() + getUpperY() + getPlotHeight() - (int)realYPosition - entry.getRadius(), 2*entry.getRadius(), 2*entry.getRadius());
				/*if(y == 79.90322580645162)
				{
					System.out.println("Found it!");
					System.out.println(((int)realXPosition + getUpperX() + leaveSpaceX() - entry.getRadius()));
					System.out.println(-leaveSpaceY() + getUpperY() + getPlotHeight() - (int)realYPosition - entry.getRadius());
					System.out.println("/////////////////////////////////////////");
					g.setColor(Color.pink);
					g.fillRect((int)realXPosition + getUpperX() + leaveSpaceX() - entry.getRadius(), -leaveSpaceY() + getUpperY() + getPlotHeight() - (int)realYPosition - entry.getRadius(), 20, 20);
				}*/
			}
			g.setColor(Color.black);
			for(int i = 0; i < numberOfXPositions; i++)
			{
				int x = (int)(leaveSpaceX() + i*velicinaPodeokaX + getUpperX());
				g.drawLine(x, getPlotHeight() + getUpperY(), x, getPlotHeight() + getUpperY() - getSizeOfPodeok());
				if(tst1 instanceof Double)
				{
					double val = minX + i * diffX;
					g.drawString(formatDouble(val), x, getPlotHeight() + getUpperY() + 20);
				}
				else 
				{
					int val = (int)(minX + i * diffX);
					g.drawString(val + "", x, getPlotHeight() + getUpperY() + 20);
				}
			}
			for(int i = 0; i < numberOfYPositions; i++)
			{
				int y = (int)(getPlotHeight() - leaveSpaceY() - i*velicinaPodeokaY);
				g.drawLine(getUpperX(), y, getUpperX() + getSizeOfPodeok(), y);
				if(tst2 instanceof Double)
				{
					double val = minY + i * diffY;
					g.drawString(formatDouble(val), 0, y + 5);
				}
				else 
				{
					int val = (int)(minY + i * diffY);
					g.drawString(val + "", 0, y + 5);
				}
			}
		}
	}
}
