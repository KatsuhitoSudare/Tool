using Microsoft.VisualBasic;
using Prism.Commands;
using Prism.Mvvm;
using System;
using PSamples.Views;
using Prism.Regions;
using Prism.Services.Dialogs;

namespace PSamples.ViewModels
{
    public class MainWindowViewModel : BindableBase
    {
        private readonly IRegionManager _regionManager;
        private readonly IDialogService _dialogService;
        private string _title = "タイトル";

        

        public string Title
        {
            get { return _title; }
            set { SetProperty(ref _title, value); }
        }

        //=================================================
        //時間更新用
        //=================================================
        public DelegateCommand SystemDateUpdateButton { get;}
        private string _systemDateLabel = DateTime.Now.ToString("yyyy/MM/dd HH:mm:ss");
        private void SysteDateButtonExecute()
        {
            SystemDateLabel = DateTime.Now.ToString("yyyy/MM/dd HH:mm:ss");
        }
        public string SystemDateLabel
        {
            get { return _systemDateLabel; }
            set { SetProperty(ref _systemDateLabel, value); }
        }

        //================================================
        //ViewA用
        //================================================
        //ViewA用のプロパティ
        public DelegateCommand ShowViewAButton { get;}
        private void ShowViewAButtonExecute()
        {
            _regionManager.RequestNavigate("ContentRegion", nameof(ViewA));
        }


        //================================================
        //ViewB用
        //================================================

        public DelegateCommand ShowViewBButton { get; }
        private void ShowViewBButtonExecute()
        {
            var p = new NavigationParameters
            {
                { nameof(ViewBViewModel.MyLabel), SystemDateLabel }
            };
            _regionManager.RequestNavigate("ContentRegion", nameof(ViewB),p);
        }


        //================================================
        //ViewC用
        //================================================
        public DelegateCommand ShowViewCButton { get; }
        private void ShowViewCButtonExecute()
        {
            _dialogService.ShowDialog(nameof(ViewC), null, null);
        }

        //コンストラクタ
        public MainWindowViewModel(IRegionManager regionManager,IDialogService dialogService)
        {
            _regionManager = regionManager;
            _dialogService = dialogService;

            SystemDateUpdateButton = new DelegateCommand(SysteDateButtonExecute);
            ShowViewAButton = new DelegateCommand(ShowViewAButtonExecute);
            ShowViewBButton = new DelegateCommand(ShowViewBButtonExecute);
            ShowViewCButton = new DelegateCommand(ShowViewCButtonExecute);
        }
    }
}
