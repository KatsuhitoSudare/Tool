using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Linq;

namespace PSamples.ViewModels
{
    public class ViewCViewModel : BindableBase,IDialogAware
    {
        public ViewCViewModel()
        {

        }

        private string _viewCTextBox = "XXX";

        public event Action<IDialogResult> RequestClose;

        public string ViewCTextBox
        {
            get { return _viewCTextBox;}
            set { SetProperty(ref _viewCTextBox, value);}
        }

        public string Title => "ViewCのタイトル";

        public bool CanCloseDialog()
        {
            return true;
        }

        public void OnDialogClosed()
        {
            
        }

        public void OnDialogOpened(IDialogParameters parameters)
        {
            
        }
    }
}
