private void Window_Loaded(object sender, RoutedEventArgs e)
{
    var root = new TreeViewItem { Header = "My Computer" };
    root.Items.Add(new TreeViewItem { Header = "C:" });
    root.Items.Add(new TreeViewItem { Header = "D:" });
    FolderTree.Items.Add(root);
}

private void FolderTree_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
{
    var selectedItem = (TreeViewItem)e.NewValue;
    var path = (string)selectedItem.Header;
    var directory = new DirectoryInfo(path);
    FileList.Items.Clear();
    foreach (var file in directory.GetFiles())
    {
        FileList.Items.Add(file.Name);
    }
}
