using System;
using System.Data.SqlClient;
using System.IO;
using System.Windows.Forms;

// Connect to your SQL database
string connectionString = "Data Source=YOUR_SERVER_NAME;Initial Catalog=YOUR_DB_NAME;User ID=YOUR_USERNAME;Password=YOUR_PASSWORD;";
using (SqlConnection connection = new SqlConnection(connectionString))
{
    connection.Open();

    // Show file explorer dialog to select an image file
    OpenFileDialog openFileDialog = new OpenFileDialog();
    openFileDialog.Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG";
    openFileDialog.Title = "Select an image file";
    if (openFileDialog.ShowDialog() == DialogResult.OK)
    {
        // Get the image file path
        string imageFilePath = openFileDialog.FileName;

        // Read the image file into a byte array
        byte[] imageData;
        using (FileStream imageFileStream = new FileStream(imageFilePath, FileMode.Open, FileAccess.Read))
        {
            using (BinaryReader binaryReader = new BinaryReader(imageFileStream))
            {
                imageData = binaryReader.ReadBytes((int)imageFileStream.Length);
            }
        }

        // Insert the image into the database
        string insertSql = "INSERT INTO your_table_name (image_column_name) VALUES (@imageData)";
        using (SqlCommand insertCommand = new SqlCommand(insertSql, connection))
        {
            insertCommand.Parameters.AddWithValue("@imageData", imageData);
            insertCommand.ExecuteNonQuery();
        }
    }
    connection.Close();
}
