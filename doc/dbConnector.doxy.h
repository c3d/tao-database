/**
 * @~english
 * @taomoduledescription{dbConnector, Connection to SQL database utilities}
 *
 * Commands to connect to database (DB) and execute SQL queries.
 *
 * This module is not a database one. It only gives access to installed database.
 * This module uses Qt interface that itself uses specific drivers for database.
 * Please refer to <a href="http://doc.qt.nokia.com/4.7/sql-driver.html">Qt
 * documentation</a> to know which database are supported, and
 * how to build and install drivers.
 *
 * Following code shows how to connect, issue a query, edit the result and
 * disconnect from the database.
 *
 * @~french
 * @taomoduledescription{dbConnector, Connexion aux bases de données}
 *
 * Commandes pour se connecter à une base de données (BD) et exécuter des
 * requêtes SQL.
 *
 * Ce module n'est pas une base de données, mais seulement un connecteur pour
 * les bases près installées. Ce module utilise l'interface Qt qui elle même
 * utilise des pilotes spécifiques pour chaque base de données. Référez-vous
 * à la <a href="http://doc.qt.nokia.com/4.7/sql-driver.html">documentation Qt</a>
 * (en anglais) pour savoir quelles bases de données sont supportées, et comment
 * construire et installer les pilotes associés.
 *
 * Le code suivant donne un exemple de connexion, requète et mise en forme du
 * résultat, déconnexion.
 *
 * @~
 @code
import dbConnector
connection "MySQL", "localhost", "test", "root", "root_pwd", 3306
query -> simple_query "test", "SELECT t1.`ID`, t1.`name` FROM t1; "
draw_table 0, 0, query
close_connection "test"
 @endcode
 *  ================== IMAGE DE LA TABLE SIMPLE ==================
 * @~english
 * All return results are made of line list, and each line is itself made of a
 * list. The first list is exactly made of two integers which are the column and
 * row number in the answer. Next list, which is the first line of the answer,
 * contains column name. This first row is included in the total row number.
 * @ref draw_table funtion is a simple tool to render a result as a table.
 *
 * @~french
 * Toutes les réponses aux requêtes sont faites de listes de ligne, et une ligne
 * est elle même une liste. La première liste contient exactement 2 entiers soit
 * le nombre de colonnes et le nombre de lignes dans la réponse qui suit. Puis
 * la liste suivante (qui correspond à la première ligne) contient le nom des
 * colonnes. Cette première ligne est incluse dans le nombre total de ligne de
 * la réponse.
 * La fontion @ref draw_table permet de représenter le résultat sous la forme
 * d'une table.
 * @~
 * ============= ILLUSTRATION DU RESULTAT AFFICHE DANS LE TEST CI-DESSUS ===============
 * @endtaomoduledescription{dbConnector}
 *
 * @{
 */


/**
 * @~english
 * Establish a database connection.
 *
 * To be used once to open the connection and enable request on DB @p dbName.
 *
 * @param bdType is one out of "DB2", "Interbase", "ODBC", "Sybase", "MySQL",
 * "OCI", "ODBC3", "PostgreSQL", "SQLite2", "SQLite3", "Firebird".
 * @param hostname is the name or IP address of the DB server.
 * @param dbName is the name of the database in the server.
 * @param userName is the name of the DB user to be connected.
 * @param password is the password for user @p userName in the DB.
 * @param port is the port number of the DB server.
 *
 * @~french
 * Crée une connexion à une base de données.
 *
 * À n'utiliser qu'une seule fois pour ouvrir une connexion et autoriser les
 * requêtes vers la base @p dbName.
 *
 * @param bdType est l'une des valeurs suivantes : "DB2", "Interbase", "ODBC",
 * "Sybase", "MySQL", "OCI", "ODBC3", "PostgreSQL", "SQLite2", "SQLite3",
 * "Firebird".
 * @param hostname est le nom ou l'adresse IP du server de BD.
 * @param dbName est le nom de la base de données au sein du server.
 * @param userName est le nom de l'utilisateur connu de la BD.
 * @param password est le mot de passe de l'utilisateur @p userName de la BD.
 * @param port est le numéro de port pour sur lequel écoute le server de BD.
 *
 */
connection(text bdType, text hostname, text dbName, text userName,
           text password, integer port);

/**
 * @~english
 * Lists tables available in the DB.
 *
 * It is equivalent to SQL request "SHOW tables"
 *
 * @param databaseName is the name of the database hosting tables to list.
 *
 * @~french
 * Liste les tables disponibles dans la BD.
 *
 * Cette commande est équivalente à la requête SQL "SHOW tables".
 *
 * @param databaseName est le nom de la BD de laquelle lister les tables.
 *
 */
table_list(text databaseName);

/**
 * @~english
 * List field name of a table.
 *
 * This is not equivalent to <tt>DESCRIBES tableName</tt> because it only
 * returns field name.
 *
 * @param databaseName is the name of the DB.
 * @param tableName is the name of the table hosting fields to list.
 *
 * @~french
 * Liste les noms des champs d'une table.
 *
 * Cette commande n'est pas équivalente à <tt>DESCRIBES tableName</tt> parce
 * qu'elle ne liste que les noms des champs.
 *
 * @param databaseName est le nom de la BD.
 * @param tableName est le nom de la table de laquelle lister les champs.
 */
field_list(text databaseName, text tableName);

/**
 * @~english
 * Execute an SQL query.
 *
 * @param databaseName is the DB name (given at connection time).
 * @param query_string is the SQL query to be executed.
 *
 * @~french
 * Execute une requête SQL.
 *
 * @param databaseName est le nom de la BD (donné à @ref connection).
 * @param query_string est la requête SQL à exécuter.
 *
 */
query(text databaseName, text query_string);

/**
 * @~english
 * Filters rows on a value.
 *
 * Returns rows where the filter apply. All the columns are in the answer.
 *
 * @param databaseName is the name of the DB.
 * @param tableName is the name of the table.
 * @param filter is a @a WHERE clause without the "where" word.
 *
 * @~french
 * Filtre les lignes sur une valeur.
 *
 * Retourne les lignes où le filtre s'applique. Toutes les colonnes sont retournées.
 *
 * @param databaseName est le nom de la BD.
 * @param tableName est le nom de la table.
 * @param filter est une clause @a WHERE sans le mot "where".
 *
 */
filter_query( text databaseName, text tableName, text filter);

/**
 * @~english
 * Replace a column by values from another table.
 *
 * All columns from @p tableName1 are returned excepted the @p primaryKey one.
 *
 * @param databaseName is the BD name.
 * @param tableName1 is the name of the main table.
 * @param filter is a @a WHERE clause applied to main table.
 * @param tableName2 is the name of the table where the complementary
 * information will be found.
 * @param primaryKey is the name of the column where to find primery key for
 * @p tableName2.
 * @param fieldNeed is the name in @p tableName2 of the column that will be used.
 * @param placeId is the place of the new column. 0 means in front of column 1.
*
 * @~french
 * Remplace une colonne par des valeurs provenant d'une autre table.
 *
 * Toutes les colonnes de @p tableName1 sont retournées à l'exception de la
 * colonne @p primaryKey.
 *
 * @param databaseName est le nom de la BD.
 * @param tableName1 est le nom de la table principale.
 * @param filter est une clause @a WHERE appliquée à la table principale.
 * @param tableName2 est le nom de la table dans laquelle les informations
 * complémentaires vont être cherchées.
 * @param primaryKey est le nom de la colonne de la table 1 qui représente la
 * clé primaire de la table 2.
 * @param fieldNeed est le nom, dans la table 2, de la colonne qui va être
 * utilisée.
 * @param placeId est l'emplacement que va prendre la colonne insérée.
 * (0 désigne l'emplacement avant la première colonne de la table 1)
 */
relational_query(text databaseName, text tableName1, text filter,
                 text tableName2, text primaryKey, text fieldNeed,
                 integer placeId);
/**
 * @~english
 * Close a connection
 *
 * @param databaseName is the name of the connection to close.
 * @~french
 * Ferme une connexion
 *
 * @param databaseName est le nom de la connexion à clore.
 */
close_connection(text databaseName);

/**
 * @~english
 * Closes all connections.
 *
 * Closes all opend connections in the driver.
 *
 * @~french
 * Ferme toutes les connexions.
 *
 * Ferme toutes les connexions ouvertes par ce driver.
 */
close_all_connection();

/**
 * @~english
 * Draw a table from a request result.
 *
 * The result is drawn as a basic table. Cell sizes, font, colors can be set.
 * The entire cell draw can be redefined with @ref draw_a_cell.
 *
 * @param x, y is the center of the table.
 * @param queryResult is the tree returned by one of @ref query,
 * @ref filter_query, @ref relational_query.
 *
 * @~french
 * Dessine une table à partir d'un résultat de requête.
 *
 * Le résultat est retranscrit sous forme d'un tableau basique. Les tailles des
 * cellule, font, couleurs peuvents être configurés, voire même le dessin complet
 * d'une cellule peut être redéfini en redéfinissant @ref draw_a_cell.
 *
 * @param x, y est le centre de la table.
 * @param queryResult est l'arbre retourné par l'une des commandes @ref query,
 * @ref filter_query, @ref relational_query.
 *
 */
draw_table( integer x, integer y, tree queryResult);

/**
 * @~english
 * Draw one cell
 *
 * @~french
 * Dessine une cellule.
 *
 * Cette fonction est appelée par @ref draw_table pour dessiner chacune des
 * cellules. Elle peut être redéfinie pour un thème différent et ainsi permettre
 * toutes les formes de cellules.
 *
 * En plus des valeurs configurables cell_* il existe des valeurs qui peuvent
 * être utilisées en lecture seulement :
 * @ref cellId, @ref row, @ref col, qui sont les valeurs courantes du numéro de
 * cellule, du numéro de ligne et de colonne.
 * Il y a aussi @ref rtable_row et @ref rtable_col qui sont les nombre total
 * de lignes et colonne à dessiner.
 *
 * @~
 * ========== ILLUSTRER AVEC LA TABLE EN BULLE ===================
 *
 */
draw_a_cell( text theme, integer col, integer row, tree value);

/**
 * @property cellId
 * @~english
 * <b>[read only]</b> Cell number.
 *
 * Starting from 1. 1 and 2 are the row and column number in the result.
 *
 * @~french
 * <b>[lecture uniquement]</b> Numéro de la cellule.
 *
 * Commence à 1. 1 et 2 sont le nombre de ligne et de colonne du résultat.
 */
integer cellId;


/**
 * @property row
 * @~english
 * <b>[read only]</b> Current row.
 *
 * Current line number. Start from zero with the heading line.
 *
 * @~french
 * <b>[lecture uniquement]</b> Ligne courante.
 *
 * Numéro de la ligne courante. Démarre à zéro avec la ligne d'entête.
 */
integer row;


/**
 * @property col
 * @~english
 * <b>[read only]</b> Current column.
 *
 * Current column number. Start from one.
 *
 * @~french
 * <b>[lecture uniquement]</b> Colonne courante.
 *
 * Numéro de colonne courante. Démarre à un.
 */
integer col;


/**
 * @property table_row
 * @~english
 * <b>[read only]</b> Total number of row.
 *
 * Total number of row in the result, inlcuding the heading row.
 *
 * @~french
 * <b>[lecture uniquement]</b> Nombre total de ligne.
 *
 * Nombre total de ligne dans la réponse, incluant la ligne d'entête.
 */
integer table_row;


/**
 * @property table_col
 * @~english
 * <b>[read only]</b> Total number of column.
 *
 * Total number of column in the result.
 *
 * @~french
 * <b>[lecture uniquement]</b>  Nombre total de colonne.
 *
 * Nombre total de colonne dans la réponse.
 */
integer table_col;

/**
 * @property cell_width
 * @~english
 * Width of a cell.
 *
 * Default value is 250.
 *
 * @~french
 * Largeur d'une cellule.
 *
 * La valeur par défaut est 250.
 */
integer cell_width;

/**
 * @property cell_height
 * @~english
 * Height of the cell.
 *
 * Default value is 70.
 *
 * @~french
 * Hauteur d'une cellule.
 *
 * La valeur par défaut est 70.
 */
integer cell_height;



/**
 * @property cell_edge_color
 * @~english
 * Cell border color.
 *
 * Color of the line around the cell. Allowed values are all those supported
 * by the @ref color command.
 *
 * @~french
 *
 *
 * La valeur par défaut est noire : "black".
 */
color cell_edge_color;


/**
 * @property
 * @~english
 *
 *
 * .
 *
 * @~french
 *
 *
 * .
 */
//cell_bg_color ->  "transparent"


/**
 * @property
 * @~english
 *
 *
 * .
 *
 * @~french
 *
 *
 * .
 */
//cell_text_color -> "font"


/**
 * @property
 * @~english
 *
 *
 * .
 *
 * @~french
 *
 *
 * .
 */
//cell_font -> font "Arial", 15

/**
 * @}
 */
