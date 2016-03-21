import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.WindowConstants;
import javax.swing.border.TitledBorder;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;


/**
 * @author Martin
 *
 */
public class GUI extends JFrame  {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private JFrame thisFrame;
	
	private String cbmcPath;
	
	private String gotoccPath;
	
	private String gotoinstrumentPath;
	
	/**
	 * 
	 */
	public GUI() {
		
		this("cbmc", "goto-cc", "goto-instrument");
		
	}
	
	/**
	 * @param cbmcPath
	 * @param gotoccPath
	 * @param gotoinstrumentPath
	 */
	public GUI(String cbmcPath, String gotoccPath, String gotoinstrumentPath) {
		
		this.cbmcPath = cbmcPath;
		
		this.gotoccPath = gotoccPath;
		
		this.gotoinstrumentPath = gotoinstrumentPath;
		
		functionsList = new HashSet<String>();
		
		thisFrame = this;
		
		generateGUI();
		
	}
	
	/**
	 * 
	 */
	private void generateGUI() {
		
		setPreferredSize(new Dimension(800, 500));
		
		setLayout(new BorderLayout());
		
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		
		JTabbedPane tabbedPane = new JTabbedPane();
		
		add(tabbedPane);
		
		setupRun(tabbedPane);
		
		setupFunctions(tabbedPane);
		
		setupQuery(tabbedPane);
		
		actionListeners();
		
		pack();
		
		setVisible(true);
		
	}
	
	/**
	 * 
	 */
	private JButton choosePath;
	
	/**
	 * 
	 */
	private JTextField chosenPath;
	
	/**
	 * 
	 */
	private JButton chooseMergePath;
	
	/**
	 * 
	 */
	private JTextField chosenMergePath;
	
	/**
	 * 
	 */
	private JTextArea outputPane;
	
	/**
	 * 
	 */
	private JTextField wordLength;
	
	/**
	 * 
	 */
	private JCheckBox automaticWordLength;
	
	/**
	 * 
	 */
	private JTextField loopBound;
	
	/**
	 * 
	 */
	private JButton run;
	
	/**
	 * 
	 */
	private JTextField functionName;
	
	/**
	 * 
	 */
	private JButton addFunction;
	
	/**
	 * 
	 */
	private JList<String> functionList;
	
	/**
	 * 
	 */
	private DefaultListModel<String> functionListModel;
	
	/**
	 * 
	 */
	private JTextField query;
	
	/**
	 * 
	 */
	private JButton checkQuery;
	
	/**
	 * 
	 */
	private JTextArea checkResult;
	
	/**
	 * @param tabbedPane
	 */
	private void setupQuery(JTabbedPane tabbedPane) {
		
		JPanel queryPanel = new JPanel();
		
		queryPanel.setLayout(new BorderLayout());
		
		tabbedPane.addTab("Query", queryPanel);
		
		//
		
		JPanel northPanel = new JPanel();
		
		northPanel.setBorder(new TitledBorder(""));
		
		northPanel.setLayout(new BorderLayout());
		
		queryPanel.add(northPanel, BorderLayout.NORTH);
		
		//
		
		query = new JTextField();
		
		northPanel.add(query, BorderLayout.CENTER);
		
		//
		
		checkQuery = new JButton("Check");
		
		northPanel.add(checkQuery, BorderLayout.EAST);
		
		////
		
		JPanel centerPanel = new JPanel();
		
		centerPanel.setBorder(new TitledBorder(""));
		
		centerPanel.setLayout(new BorderLayout());
		
		queryPanel.add(centerPanel, BorderLayout.CENTER);
		
		//
		
		checkResult = new JTextArea();
		
		centerPanel.add(checkResult, BorderLayout.CENTER);
		
	}
	
	/**
	 * @param tabbedPane
	 */
	private void setupFunctions(JTabbedPane tabbedPane) {
		
		JPanel functionPanel = new JPanel();
		
		functionPanel.setLayout(new BorderLayout());
		
		tabbedPane.addTab("Functions", functionPanel);
		
		//
		
		JPanel northPanel = new JPanel();
		
		northPanel.setBorder(new TitledBorder(""));
		
		northPanel.setLayout(new BorderLayout());
		
		functionPanel.add(northPanel, BorderLayout.NORTH);
		
		//
		
		functionName = new JTextField();
		
		northPanel.add(functionName, BorderLayout.CENTER);
		
		//
		
		addFunction = new JButton("Add function");
		
		northPanel.add(addFunction, BorderLayout.EAST);
		
		////
		
		JPanel centerPanel = new JPanel();
		
		centerPanel.setBorder(new TitledBorder(""));
		
		centerPanel.setLayout(new BorderLayout());
		
		functionPanel.add(centerPanel, BorderLayout.CENTER);
		
		//
		
		functionList = new JList<String>();
		
		functionListModel = new DefaultListModel<String>();
		
		functionList.setModel(functionListModel);
		
		centerPanel.add(functionList, BorderLayout.CENTER);
		
		////////////////// Temporary for current example //////////////
		
		functionListModel.addElement("Non_Crossing_Biased_Climb");
		
		functionListModel.addElement("ALIM");
		
		functionListModel.addElement("Inhibit_Biased_Climb");
		
		functionListModel.addElement("Non_Crossing_Biased_Descend");
		
		functionListModel.addElement("Own_Below_Threat");
		
		functionListModel.addElement("Own_Above_Threat");
		
		functionListModel.addElement("alt_sep_test");
		
		functionListModel.addElement("initialize");
		
		functionListModel.addElement("fake0");
		
		functionListModel.addElement("fake1");
		
		////////////////////////////////////////////////////
		
	}
	
	/**
	 * 
	 */
	private void setupRun(JTabbedPane tabbedPane) {
		
		JPanel runPanel = new JPanel();
		
		runPanel.setLayout(new BorderLayout());
		
		tabbedPane.addTab("Run", runPanel);
		
		//
		
		JPanel northPanel = new JPanel();
		
		northPanel.setLayout(new BorderLayout());
		
		runPanel.add(northPanel, BorderLayout.NORTH);
		
		//
		
		JPanel fileLocationPanel = new JPanel();
		
		fileLocationPanel.setBorder(new TitledBorder(""));
		
		fileLocationPanel.setLayout(new BorderLayout());
		
		//
		
		northPanel.add(fileLocationPanel, BorderLayout.NORTH);
		
		//
		
		chosenPath = new JTextField();
		
		chosenPath.setText("");
		
		chosenPath.setEnabled(false);
		
		fileLocationPanel.add(chosenPath, BorderLayout.CENTER);
		
		//
		
		JPanel buttonPanel = new JPanel();
		
		choosePath = new JButton("Select file");
		
		buttonPanel.add(choosePath);
		
		fileLocationPanel.add(buttonPanel, BorderLayout.EAST);
		
		//
		
		final JButton showMerge = new JButton("+");
		
		buttonPanel.add(showMerge);
		
		//
		
		final JPanel mergeLocationPanel = new JPanel();
		
		mergeLocationPanel.setBorder(new TitledBorder(""));
		
		mergeLocationPanel.setLayout(new BorderLayout());
		
		mergeLocationPanel.setVisible(false);
		
		showMerge.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				
				mergeLocationPanel.setVisible(!mergeLocationPanel.isVisible());
				
				String buttonText = showMerge.getText().equals("+") ? "-" : "+";
				
				showMerge.setText(buttonText);
				
				chosenMergePath.setText("");
				
			}
			
		});
		
		//
		
		northPanel.add(mergeLocationPanel, BorderLayout.SOUTH);
		
		//
		
		chosenMergePath = new JTextField();
		
		chosenMergePath.setText("");
		
		chosenMergePath.setEnabled(false);
		
		mergeLocationPanel.add(chosenMergePath, BorderLayout.CENTER);
		
		//
		
		chooseMergePath = new JButton("Compare file");
		
		mergeLocationPanel.add(chooseMergePath, BorderLayout.EAST);
		
		////
		
		JPanel centerPanel = new JPanel();
		
		centerPanel.setBorder(new TitledBorder(""));
		
		centerPanel.setLayout(new BorderLayout());
		
		runPanel.add(centerPanel, BorderLayout.CENTER);
		
		//
		
		outputPane = new JTextArea();
		
		outputPane.setEnabled(false);
		
		setOutputStream(outputPane);
		
		JScrollPane outputPanelScroll = new JScrollPane(outputPane, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		
		//outputPanelScroll.setPreferredSize(new Dimension(200, 200));
		
		centerPanel.add(outputPanelScroll, BorderLayout.CENTER);
		
		////
		
		JPanel southPanel = new JPanel();
		
		southPanel.setBorder(new TitledBorder(""));
		
		southPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
		
		runPanel.add(southPanel, BorderLayout.SOUTH);
		
		//
	
		final JLabel wordLengthLabel = new JLabel("Word length:");
		
		southPanel.add(wordLengthLabel);
		
		wordLength = new JTextField();
		
		wordLength.setPreferredSize(new Dimension(50, 25));
		
		wordLength.setEnabled(false);
		
		southPanel.add(wordLength);
		
		//
		
		automaticWordLength = new JCheckBox("Automatic");
		
		automaticWordLength.setSelected(true);
		
		southPanel.add(automaticWordLength);
		
		//
		
		final JLabel loopBoundLabel = new JLabel("Loop bound:");
		
		southPanel.add(loopBoundLabel);
		
		loopBound = new JTextField();
		
		loopBound.setPreferredSize(new Dimension(50, 25));
		
		loopBound.setText("1");
		
		southPanel.add(loopBound);
		
		//
		
		final JLabel membershipQueryLabel = new JLabel("Membership Query:");
		
		southPanel.add(membershipQueryLabel);
		
		membershipQueryLabel.setVisible(false);
		
		final JTextField membershipQuery = new JTextField();
		
		membershipQuery.setPreferredSize(new Dimension(250, 25));
		
		membershipQuery.setVisible(false);
		
		southPanel.add(membershipQuery);
		
		//
		
		final JCheckBox membershipQueryOnly = new JCheckBox("Membership query only?");
		
		membershipQueryOnly.setSelected(false);
		
		membershipQueryOnly.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				
				membershipQueryLabel.setVisible(!membershipQueryLabel.isVisible());
				
				membershipQuery.setVisible(!membershipQuery.isVisible());
				
				//
				
				wordLengthLabel.setVisible(!wordLengthLabel.isVisible());
				
				wordLength.setVisible(!wordLength.isVisible());
				
				loopBound.setVisible(!loopBound.isVisible());
				
				loopBoundLabel.setVisible(!loopBoundLabel.isVisible());
				
				automaticWordLength.setVisible(!automaticWordLength.isVisible());
				
			}
			
		});
		
		southPanel.add(membershipQueryOnly);
		
		//
		
		run = new JButton("Run");
		
		southPanel.add(run);
		
		//
		
	}
	
	/**
	 * @param textArea
	 */
	private void setOutputStream(final JTextArea textArea) {
		
		final class CustomOutputStream extends OutputStream {
	
			private JTextArea textArea;
			
			private final StringBuilder sb;
			
		    public CustomOutputStream(JTextArea textArea) {
		    
		    	this.textArea = textArea;
		    	
		    	sb = new StringBuilder();
		    
		    }
		    
		    @Override
		    public void write(int b) throws IOException {
		        
		        /*if (b == '\r') return;

		        if (b == '\n') {
		        	
		           final String text = sb.toString() + "\n";*/
		           
	        	   textArea.append(String.valueOf((char) b));
	        		   
		           /*sb.setLength(0);

		           return;
		           
		        }

		        sb.append((char) b);*/
		        
		    }
		
		}
		
		//
		
		PrintStream printStream = new PrintStream(new CustomOutputStream(textArea), true);
		
		System.setOut(printStream);
		
		System.setErr(printStream);
		
	}
	
	private HashSet<String> functionsList;
	
	private static final String APPLICATION = "./pv"; // Previously: libalf/examples/online
	
	/**
	 * 
	 */
	private void actionListeners() {
		
		choosePath.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				
				JFileChooser fc = new JFileChooser();
				
				int returnVal = fc.showOpenDialog(GUI.this);

		        if (returnVal == JFileChooser.APPROVE_OPTION) {
		            
		        	chosenPath.setText(fc.getSelectedFile().toString());
		
		        }
		        
			}
			
		});
		
		chooseMergePath.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				
				JFileChooser fc = new JFileChooser();
				
				int returnVal = fc.showOpenDialog(GUI.this);

		        if (returnVal == JFileChooser.APPROVE_OPTION) {
		            
		        	chosenMergePath.setText(fc.getSelectedFile().toString());
		
		        }
		        
			}
			
		});
		
		chosenPath.getDocument().addDocumentListener(new DocumentListener() {
		
			@Override
			public void insertUpdate(DocumentEvent e) {
				
				updateFunctionList();
				
			}

			@Override
			public void removeUpdate(DocumentEvent e) {
				
				updateFunctionList();
				
			}

			@Override
			public void changedUpdate(DocumentEvent e) {
				
				updateFunctionList();
				
			}
		
			private void updateFunctionList() {
				
				runCommand(gotoccPath + " " + chosenPath.getText() + " -o temp.o");
				
				runCommand(gotoinstrumentPath + " --learn temp.o temp.o");
				
				functionListModel.removeAllElements();
				
				for ( String function : readFromFile("func_names.data") ) {
					
					functionListModel.addElement(function.trim());
					
					functionsList.add(function.trim());
					
				}
				
				try {
				      
				    File fileTemp = new File(chosenPath.getText().substring(0, chosenPath.getText().length() - 2) + ".f");
				    
				    if ( fileTemp.exists() ) {
				    	
				    	fileTemp.delete();
				    
				    }   
				
				} catch(Exception e) {
				
				     e.printStackTrace();
				     
				}
				
			}
		
		});

		run.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				
				new Thread(new Runnable() {
				       
					public void run() {
						
						outputPane.setText("");
						
						if ( !automaticWordLength.isSelected() ) {
							
							if ( !chosenMergePath.getText().equals("") ) {
								
								runCommand(APPLICATION + " --compare " + chosenPath.getText() + " " + chosenMergePath.getText() + " " + wordLength.getText() + " --auto f --v --user-unwind " + loopBound.getText());
								
							} else {
								
								runCommand(APPLICATION + " " + chosenPath.getText() + " " + wordLength.getText() + " --auto f --v --user-unwind " + loopBound.getText());
								
							}
							
						} else {
						
							if ( !chosenMergePath.getText().equals("") ) {
							
								runCommand(APPLICATION + " --compare " + chosenPath.getText() + " " + chosenMergePath.getText() + " 0 --auto f --v --user-unwind " + loopBound.getText());
						
							} else {
								
								runCommand(APPLICATION + " " + chosenPath.getText() + " 0 --auto f --v --user-unwind " + loopBound.getText());
								
							}
							
						}
						
					}
				
		        }).start();
				
			}
			
		});
		
		automaticWordLength.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				
				wordLength.setEnabled(!wordLength.isEnabled());
				
				if ( wordLength.getText().equals("") ) {
					
					wordLength.setText("1"); 
				
				} else {
					
					wordLength.setText("");
					
				}
				
			}
			
		});
		
		functionList.addMouseListener(new MouseAdapter() {
			
			public void mouseClicked(MouseEvent evt) {
		        
				@SuppressWarnings("unchecked")
				JList<String> list = (JList<String>)evt.getSource();
		        
		        if (evt.getClickCount() == 2) {

		            functionListModel.remove(list.locationToIndex(evt.getPoint()));
		          
			        String functionNamesFile = chosenPath.getText().substring(0, chosenPath.getText().length() - 2) + ".f"; 
			        
			        clearFile(functionNamesFile);
			        
			        for ( int i = 0; i < functionListModel.size(); i++ ) {
			        
			        	writeToFile(functionNamesFile, functionListModel.get(i));
			        	
			        }
			        
		        }
		        
		    }
			
		});
		
		addFunction.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				
				if ( functionName.getText().equals("") ) return;
				
				if ( new ArrayList<String>(Collections.list(functionListModel.elements())).contains(functionName.getText().trim()) ) return;
				
				if ( !new ArrayList<String>(functionsList).contains(functionName.getText().trim())) JOptionPane.showMessageDialog(thisFrame, "The function you have entered cannot be found from analysing the program supplied. Please ensure it exists.");
				
				functionListModel.addElement(functionName.getText());
				
			}
			
		});
		
		// TODO: unwinding and word length as variables
		checkQuery.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				
				ArrayList<String> returned;
				
				if ( functionListModel.getSize() > 0 ) {
					
					String functionList = "";
					
					for ( int i = 0; i < functionListModel.getSize(); i++ ) {
					
						functionList += functionListModel.getElementAt(i) + " ";
						
					}
					
					returned = runCommandWithReturn(APPLICATION + " --configuration external_query --external_query_word \"" + query.getText() + "\"" 
							+ " --start-user-unwinding 1 --end-user-unwinding 1 --start-max-word-length 12 --end-max-word-length 12 "
							+ "--instrument-functions \"" + functionList + "\"" 
							+ chosenPath.getText() + " 0 --auto f --v --user-unwind " + loopBound.getText()); // Unsure about use of `auto' etc in pv version?
					
				} else {
					
					returned = runCommandWithReturn(APPLICATION + " --configuration external_query --external_query_word \"" + query.getText() + "\"" 
							+ " --start-user-unwinding 1 --end-user-unwinding 1 --start-max-word-length 12 --end-max-word-length 12 "  
							+ chosenPath.getText() + " 0 --auto f --v --user-unwind " + loopBound.getText());
					
				}
				
				checkResult.setText("Query in language");
				
				for ( String output : returned ) {
					
					if ( output.contains("not_in_language") ) {
						
						checkResult.setText("Query not in language");
						
						// Show counterexample
						
					}
					
				}
				
			}
			
		});
		
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		new GUI();
		
	}
	
	/**
	 * @param command
	 */
	private void runCommand(String command) {

		runCommandWithReturn(command);
	    
	}
	
	/**
	 * @param command
	 * @return
	 */
	public final static ArrayList<String> runCommandWithReturn(String command) {
		
		ArrayList<String> returnLines = new ArrayList<String>();
		
		Process proc = null;
		
		try {
			
			proc = Runtime.getRuntime().exec(command);
		
		} catch (IOException e1) {
			
			e1.printStackTrace();
		
		}
		
		BufferedReader outputs = new BufferedReader(new InputStreamReader(proc.getInputStream()));
		
		BufferedReader errors = new BufferedReader(new InputStreamReader(proc.getErrorStream()));
		  
		String line = null;  
		 
		try {
			
			while ((line = outputs.readLine()) != null) {  
			
				returnLines.add(line); 

				System.out.println(line);
			
			}
			
		} catch (IOException e1) {
			
			e1.printStackTrace();
		
		}
		
		try {
		
			while ((line = errors.readLine()) != null) {  
				
				returnLines.add(line); 
				
				System.out.println(line);
			
			}
			
		} catch (IOException e1) {
			
			e1.printStackTrace();
		
		} 
		  
		try {
		
			proc.waitFor();
		
		} catch (InterruptedException e) { 
			
			System.out.println(e); 
			
			returnLines.add(e.getMessage()); 
			
		}
	    
		return returnLines;
		
	}
	
	/**
	 * @param url
	 * @return
	 */
	private ArrayList<String> readFromFile(String url) {
		
		ArrayList<String> lines = new ArrayList<String>();
		
		BufferedReader br = null;
	       
  		try {
   
  			String sCurrentLine;
   
  			br = new BufferedReader(new FileReader(url));
   
  			while ((sCurrentLine = br.readLine()) != null) {
  				
  				lines.add(sCurrentLine);
  				
  			}
   
  		} catch (IOException e) {
  			
  			e.printStackTrace();
  		
  		} finally {
  		
  			try {
  			
  				if (br != null) br.close();
  			
  			} catch (IOException ex) {
  			
  				ex.printStackTrace();
  			
  			}
  		
  		}
  		
  		return lines;
  		
	}
	
	/**
	 * 
	 */
	public static void clearFile(String URL) {
		
		PrintWriter writer = null;
		try {
			writer = new PrintWriter(new File(URL));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		writer.print("");
		writer.close();
		
	}
	
	/**
	 * @param url
	 * @param content
	 */
	public static void writeToFile(String url, String content) {
		
		FileWriter writer = null;
		
		try {
			
			writer = new FileWriter(url, true);
		
		} catch (IOException e) { 
			
			e.printStackTrace();
			
		}
		
		try {
	
			writer.append(content);
	
		    writer.flush();
		
		} catch(IOException e) {
			
			System.err.println(e.getMessage());
		
		}
		
	}
	
}
