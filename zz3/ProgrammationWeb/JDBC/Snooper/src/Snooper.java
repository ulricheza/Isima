
import java.sql.*;
import java.util.StringTokenizer;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Snooper extends JPanel implements ActionListener {

    JLabel index;
    JComboBox publicTableList;
    JComboBox privateTableList;
    String tableNames[], tableNamesAsOne;
    JLabel id;
    TextArea content;
    Connection link;
    String myURL = "jdbc:odbc:";
    java.sql.DatabaseMetaData patrol;

    /*	***********	*/
    /*	CONSTRUCTOR	*/
    /*	***********	*/
    public Snooper(String source) throws SQLException {
        super(new BorderLayout());
        connect(source);
        inspect(source);
    }

    /*	***************************	*/
    /*	CONNECTING TO THE DATA BASE	*/
    /*	***************************	*/
    public void connect(String source) {
        try {
            DriverManager.registerDriver(new sun.jdbc.odbc.JdbcOdbcDriver());
            link = DriverManager.getConnection(myURL + source);
        } catch (SQLException e) {
            System.out.println("Connection error: " + e.getMessage());
        }
    }

    /*	***********************************	*/
    /*	INSPECTING THE DATA BASE STRUCTURE	*/
    /*	***********************************	*/
    public void inspect(String source) throws SQLException {
        patrol = link.getMetaData();
        id = new JLabel("DATA BASE " + source + " (User: " + patrol.getUserName() + ")");
        add(id, BorderLayout.NORTH);
        add(new JLabel("TABLES: "), BorderLayout.WEST);
        ResultSet answer = patrol.getTables(null, null, null, null);
        while (answer.next()) {
            if (answer.wasNull() == false) {
                tableNamesAsOne = tableNamesAsOne + answer.getString("TABLE_NAME") + " ";
            }
        }
        answer.close();
        StringTokenizer st = new StringTokenizer(tableNamesAsOne, " ");
        tableNames = new String[st.countTokens()];
        while (st.hasMoreTokens()) {
            tableNames[st.countTokens() - 1] = st.nextToken();
        }
        publicTableList = new JComboBox(tableNames);
        publicTableList.setSelectedIndex(0);
        publicTableList.addActionListener(this);
        add(publicTableList, BorderLayout.EAST);
        content = new TextArea();
        add(content, BorderLayout.SOUTH);
        updateFields(tableNames[publicTableList.getSelectedIndex()]);
    }

    /*	***************************	*/
    /*	LISTENING TO THE COMBO BOX	*/
    /*	***************************	*/
    public void actionPerformed(ActionEvent e) {
        JComboBox cb = (JComboBox) e.getSource();
        String tableName = (String) cb.getSelectedItem();
        updateFields(tableName);
    }

    /*	***********************	*/
    /*	UPDATING THE FIELD LIST	*/
    /*	***********************	*/
    protected void updateFields(String name) {
        content.setText("");	// empty the content first
        try {
            ResultSet answer = patrol.getTables(null, null, null, null);
            while (answer.next()) {
                if (answer.wasNull() == false) {
                    if (name.equalsIgnoreCase(answer.getString("TABLE_NAME")) == true) {
                        content.append("CATEGORY = " + answer.getString("TABLE_CAT") + '\n');
                        content.append("TYPE = " + answer.getString("TABLE_TYPE") + '\n');
                        content.append("SCHEMA = " + answer.getString("TABLE_SCHEM") + '\n');
                        content.append("REMARKS = " + answer.getString("REMARKS"));
                    }
                }
            }
        } catch (SQLException e) {
            System.out.println("Meta data error");
        }
    }

    private static void createAndShowGUI(String source) throws SQLException {
        //Create and set up the window.
        JFrame frame = new JFrame("Snooper");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //Create and set up the content pane.
        JComponent newContentPane = new Snooper(source);
        newContentPane.setOpaque(true);
        frame.setContentPane(newContentPane);
        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }

    /*	***********	*/
    /*	LAUNCHING	*/
    /*	***********	*/
    public static void main(String[] args) throws SQLException {
        createAndShowGUI(args[0]);
    }
}
