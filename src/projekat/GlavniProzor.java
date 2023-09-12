package projekat;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;

public class GlavniProzor extends JFrame {
	
	JPanel southPanel;
	JPanel southPanelSection1;//loading section
	JPanel southPanelSection2;//filter section
	JPanel southPanelSection3;//show what?
	JTextField athletesPathTextField;
	JButton loadAthletesButton;
	JTextField eventsPathTextField;
	JButton loadEventsButton;
	JTextField sportFilterTextField;
	JTextField godinaFilterTextField;
	JTextField dogadjajFilterTextField;
	JTextField medaljaFilterTextField;
	JCheckBox sportFilterCB;
	JCheckBox yearFilterCB;
	JCheckBox eventFilterCB;
	JCheckBox medalFilterCB;
	Graph currentGraph;
	
	
	SysClass sys;
	
	public GlavniProzor()
	{
		populateWindow();
		setVisible(true);
		pack();
		sys = new SysClass();
	}
	
	private void populateWindow()
	{
		southPanel = new JPanel();
		southPanel.setLayout(new GridLayout(0, 1, 0, 10));
		
		///////////////////////////////////////////////////////////////////////
		southPanelSection1 = new JPanel(new GridLayout(0,2,5,10));
		
		athletesPathTextField = new JTextField(30);
		loadAthletesButton = new JButton("Ucitaj sportiste");
		
		loadAthletesButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				String path = athletesPathTextField.getText();
				if(path == null || path.equals(""))return;
				sys.loadAthletes(path);
				System.out.println("Athletes loading finished!");
				loadAthletesButton.setEnabled(false);
				loadEventsButton.setEnabled(true);
				//C:\\Users\\Aleksa\\eclipse-workspace\\POOP2\\src\\projekat\\athletes.txt
			}
		});
		
		southPanelSection1.add(athletesPathTextField);
		southPanelSection1.add(loadAthletesButton);
		
		
		JCheckBox cbIndividualMode = new JCheckBox("Individual mode");
		JTextField yearTextField = new JTextField(30);
		southPanelSection1.add(cbIndividualMode);
		southPanelSection1.add(yearTextField);
		
		eventsPathTextField = new JTextField(30);
		loadEventsButton = new JButton("Ucitaj events");
		
		loadEventsButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				String path = eventsPathTextField.getText();
				if(path == null || path.equals(""))return;
				if(cbIndividualMode.isSelected())
				{
					sys.loadIndividualMode(path, Integer.valueOf(yearTextField.getText()));
				}
				else sys.loadGroupMode(path);
				
				//sys.loadIndividualMode(path, 2016);
				
				
				loadEventsButton.setEnabled(false);
				//sys.loadGroupMode("C:\\Users\\Aleksa\\eclipse-workspace\\POOP2\\src\\projekat\\events.txt");
				System.out.println("Events loading finished!");
			}
		});
		loadEventsButton.setEnabled(false);
		
		southPanelSection1.add(eventsPathTextField);
		southPanelSection1.add(loadEventsButton);
		
		southPanel.add(southPanelSection1);
		///////////////////////////////////////////////////////////////////////
		
		southPanelSection2 = new JPanel(new GridLayout(0, 2));
		
		//JPanel southPanelSection2Subsection1 = new JPanel();
		sportFilterCB = new JCheckBox("Sport filter");
		yearFilterCB = new JCheckBox("Godina filter");
		eventFilterCB = new JCheckBox("Filter na osnovu tipa dogadjaja");
		medalFilterCB = new JCheckBox("Filter na osnovu medalje");
		sportFilterTextField = new JTextField(15);
		godinaFilterTextField = new JTextField(15);
		dogadjajFilterTextField = new JTextField(15);
		medaljaFilterTextField = new JTextField(15);
		southPanelSection2.add(sportFilterCB);
		southPanelSection2.add(sportFilterTextField);
		southPanelSection2.add(yearFilterCB);
		southPanelSection2.add(godinaFilterTextField);
		southPanelSection2.add(eventFilterCB);
		southPanelSection2.add(dogadjajFilterTextField);
		southPanelSection2.add(medalFilterCB);
		southPanelSection2.add(medaljaFilterTextField);
		
		JCheckBox opsegCB = new JCheckBox("Opseg");
		JPanel pomPanel = new JPanel();
		JTextField opsegTextFieldmin= new JTextField(15);
		JTextField opsegTextFieldmax = new JTextField(15);
		pomPanel.add(opsegTextFieldmin);
		pomPanel.add(opsegTextFieldmax);
		southPanelSection2.add(opsegCB);
		southPanelSection2.add(pomPanel);
		
		

		southPanel.add(southPanelSection2);
		
		///////////////////////////////////////////////////////////////////////
		
		southPanelSection3 = new JPanel(new GridLayout(0, 1, 0, 5));
		
		
		JLabel prikazLabel = new JLabel("Prikaz:");
		southPanelSection3.add(prikazLabel);
		
		ButtonGroup cbGroup1 = new ButtonGroup();
		JRadioButton CB0 = new JRadioButton("Broj ucesnika na svim dogadjajima na Olimpijskim igrama", true);
		JRadioButton CB1 = new JRadioButton("Ukupan broj disciplina na Olimpijskim igrama", false);
		JRadioButton CB2 = new JRadioButton("Prosecna visina svih sportista", false);
		JRadioButton CB3 = new JRadioButton("Prosecna tezina svih sportista", false);
		cbGroup1.add(CB0);
		cbGroup1.add(CB1);
		cbGroup1.add(CB2);
		cbGroup1.add(CB3);
		southPanelSection3.add(CB0);
		southPanelSection3.add(CB1);
		southPanelSection3.add(CB2);
		southPanelSection3.add(CB3);
		
		
		JButton prikaziButton = new JButton("Prikazi");
		
		prikaziButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				String sportName="", type="", medal="";
				Integer year=-1;
				if(sportFilterCB.isSelected())
				{
					if(sportFilterTextField.getText() != null)sportName = sportFilterTextField.getText();
				}
				if(eventFilterCB.isSelected())
				{
					if(eventsPathTextField.getText() != null)type = dogadjajFilterTextField.getText();
					System.out.println("Tip je : " + type);
				}
				if(medalFilterCB.isSelected())
				{
					if(medaljaFilterTextField.getText() != null)medal = medaljaFilterTextField.getText();
				}
				if(yearFilterCB.isSelected())
				{
					year = Integer.valueOf(godinaFilterTextField.getText());
				}
				if(CB0.isSelected())
				{
					if(currentGraph != null)currentGraph.getParent().remove(currentGraph);
					Map<String,Integer> mp = sys.numberOfParticipantsGroupedByCountry(sportName, year, type, medal);
					PieChart pieChart = new PieChart(mp, 10);
					pieChart.setDataMap(mp);
					currentGraph = pieChart;
					currentGraph.setPreferredSize(new Dimension(300,300));
					GlavniProzor.this.add(currentGraph,BorderLayout.CENTER);
				}
				if(CB1.isSelected())
				{
					if(currentGraph != null)currentGraph.getParent().remove(currentGraph);
					Map<String,Integer> mp = sys.numberOfDisciplinesGroupedByOlGames(sportName, year, type, medal);
					int opsegMin = 0;
					int opsegMax = 10000;
					if(opsegCB.isSelected())
					{
						if(opsegTextFieldmin.getText().equals("") || opsegTextFieldmax.getText().equals(""))return;
						opsegMin = Integer.valueOf(opsegTextFieldmin.getText());
						opsegMax = Integer.valueOf(opsegTextFieldmax.getText());
					}
					XYGraph <Integer, Integer> xyGraph = new XYGraph<Integer,Integer>(10, 10,opsegMin,opsegMax);//IZMENITI!
					for(Entry<String, Integer> entry : mp.entrySet())
					{
						if(entry.getKey().contains("Winter"))
							xyGraph.addPoint(SysClass.getYearFromString(entry.getKey()), entry.getValue(), Color.blue);
						else if(entry.getKey().contains("Summer"))
							xyGraph.addPoint(SysClass.getYearFromString(entry.getKey()), entry.getValue(), Color.red);
						else
							xyGraph.addPoint(SysClass.getYearFromString(entry.getKey()), entry.getValue(), Color.black);
					}
					currentGraph = xyGraph;
					currentGraph.setPreferredSize(new Dimension(300,300));
					GlavniProzor.this.add(currentGraph,BorderLayout.CENTER);
				}
				if(CB2.isSelected() || CB3.isSelected())
				{
					if(currentGraph != null)currentGraph.getParent().remove(currentGraph);
					Map<String,Double> mp;
					if(CB2.isSelected())
					{
						mp = sys.averageHeightGroupedByOlGames(sportName, year, type, medal);
					}
					else
					{
						mp = sys.averageWeightGroupedByOlGames(sportName, year, type, medal);
					}
					int opsegMin = 0;
					int opsegMax = 10000;
					if(opsegCB.isSelected())
					{
						if(opsegTextFieldmin.getText().equals("") || opsegTextFieldmax.getText().equals(""))return;
						opsegMin = Integer.valueOf(opsegTextFieldmin.getText());
						opsegMax = Integer.valueOf(opsegTextFieldmax.getText());
					}
					XYGraph <Integer, Double> xyGraph = new XYGraph<Integer, Double>(10, 10,opsegMin,opsegMax);//IZMENITI!
					for(Entry<String, Double> entry : mp.entrySet())
					{
						if(entry.getKey().contains("Winter"))
							xyGraph.addPoint(SysClass.getYearFromString(entry.getKey()), entry.getValue(), Color.blue);
						else if(entry.getKey().contains("Summer"))
							xyGraph.addPoint(SysClass.getYearFromString(entry.getKey()), entry.getValue(), Color.red);
						else
							xyGraph.addPoint(SysClass.getYearFromString(entry.getKey()), entry.getValue(), Color.black);
					}
					currentGraph = xyGraph;
					currentGraph.setPreferredSize(new Dimension(300,300));
					GlavniProzor.this.add(currentGraph,BorderLayout.CENTER);
				}
				GlavniProzor.this.pack();
			}
		});
		southPanelSection3.add(prikaziButton);
		
		
		southPanel.add(southPanelSection3);
		
		///////////////////////////////////////////////////////////////////////
		
		
		add(southPanel, BorderLayout.SOUTH);
		
		/*
		Map<String,Integer> mpaa = new HashMap<String,Integer>();
		mpaa.put("Srbija", 200);
		mpaa.put("Bru",122);
		mpaa.put("Brug",190);
		mpaa.put("Bruasdas",123);
		PieChart pc = new PieChart(mpaa,2);
		pc.setPreferredSize(new Dimension(300, 300));
		add(pc,BorderLayout.CENTER);
		*/
		
		/*
		SysClass sys = new SysClass();
		sys.loadAthletes("C:\\Users\\Aleksa\\eclipse-workspace\\POOP2\\src\\projekat\\athletes.txt");
		System.out.println("Here!");
		sys.loadGroupMode("C:\\Users\\Aleksa\\eclipse-workspace\\POOP2\\src\\projekat\\events.txt");
		
		Map<String, Integer> mp = sys.numberOfParticipantsGroupedByCountry("Football", -1, "", "");
		
		System.out.println("Here!");
		
		for(Entry<String, Integer> entry : mp.entrySet())
		{
			System.out.println(entry.getKey() + " -> " + entry.getValue());
		}
		*/
		
		
		
		/*
		sys.loadAthletes("C:\\Users\\Aleksa\\eclipse-workspace\\POOP2\\src\\projekat\\athletes.txt");
		System.out.println("Here!");
		sys.loadGroupMode("C:\\Users\\Aleksa\\eclipse-workspace\\POOP2\\src\\projekat\\events.txt");
		
		Map<String, Double> mp = sys.averageHeightGroupedByOlGames("Basketball", -1, "", "");
		
		System.out.println("Here!");
		
		for(Entry<String, Double> entry : mp.entrySet())
		{
			if(entry == null)continue;
			System.out.println(entry.getKey() + " -> " + entry.getValue());
		}
		
		XYGraph<Integer, Double> gr = new XYGraph<Integer, Double>(7, 6);
		gr.setPreferredSize(new Dimension(300, 300));
		for(Entry<String, Double> entry : mp.entrySet())
		{
			if(entry == null)continue;
			if(entry.getKey().contains("Winter"))
				gr.addPoint(SysClass.getYearFromString(entry.getKey()), entry.getValue(), Color.blue);
			else if(entry.getKey().contains("Summer"))
				gr.addPoint(SysClass.getYearFromString(entry.getKey()), entry.getValue(), Color.red);
			else
				gr.addPoint(SysClass.getYearFromString(entry.getKey()), entry.getValue(), Color.black);
			System.out.println(entry.getKey() + " -------> " + SysClass.getYearFromString(entry.getKey()));
		}
		add(gr,BorderLayout.CENTER);
		*/
		
		
		
		
		
		
		
		
		
		
		
		/*
		XYGraph<Double, Integer> gr = new XYGraph<Double, Integer>(7, 6);
		gr.setPreferredSize(new Dimension(300, 300));
		for(int i = 0; i < 100; i++)
		{
			gr.addPoint((double)i + 5, i + 12, Color.blue);
		}
		add(gr,BorderLayout.CENTER);
		*/
	}
	
	public static void main(String[] args)
	{
		new GlavniProzor();
	}
}
