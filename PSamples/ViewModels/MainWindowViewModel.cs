using Microsoft.VisualBasic;
using Prism.Commands;
using Prism.Mvvm;
using System;
using PSamples.Views;
using Prism.Regions;

namespace PSamples.ViewModels
{
    public class MainWindowViewModel : BindableBase
    {
        private readonly IRegionManager _regionManager;

        private string _title = "タイトル";
        public string Title
        {
            get { return _title; }
            set { SetProperty(ref _title, value); }
        }

        public DelegateCommand SystemDateUpdateButton { get;}
        public DelegateCommand ShowViewAButton { get;}

        private void ShowViewAButtonExecute()
        {
            _regionManager.RequestNavigate("ContentRegion", nameof(ViewA));
        }

        private void SysteDateButtonExecute()
        {
            SystemDateLabel = DateTime.Now.ToString("yyyy/MM/dd HH:mm:ss");
        }

        //コンストラクタ
        public MainWindowViewModel(IRegionManager regionManager)
        {
            _regionManager = regionManager;
            SystemDateUpdateButton = new DelegateCommand(SysteDateButtonExecute);
            ShowViewAButton = new DelegateCommand(ShowViewAButtonExecute);

        }
        private string _systemDateLabel = DateTime.Now.ToString("yyyy/MM/dd HH:mm:ss");
        

        public string SystemDateLabel
        {
            get { return _systemDateLabel; }
            set { SetProperty(ref _systemDateLabel, value); }
        }
    }
}
