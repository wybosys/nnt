
# include "Foundation+NNT.h"
# include "MainController.h"
# include "FsSamba.h"
# include "Directory+NNT.h"
# include "FsLocal.h"

NNTAPP_BEGIN

MainView::MainView()
{
    samba.set_text(@"SAMBA");
    bundle.set_text(@"BUNDLE");
    
    add_sub(samba);
    add_sub(bundle);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (pixel)30 << (pixel)30 << (flex)1;

    lyt << lnr;
    samba.set_frame(lyt << lnr);
    bundle.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().samba.connect(kSignalButtonClicked, _action(_class::act_samba), this);
    view().bundle.connect(kSignalButtonClicked, _action(_class::act_bundle), this);
}

void MainController::act_samba()
{
    filesystem::Samba fs;
    fs.open("192.168.170.35/shared", "shared", "shared");
    file_io fd = fs.fopen("README", filesystem::Samba::FLAG_READ);
    if (fd)
    {
        struct ::stat st;
        if (fs.fstat(fd, &st))
            trace_int((int)st.st_size);
        core::data stm(st.st_size);
        fs.fread(fd, stm);
        trace_msg(core::type_cast<ns::String>(stm));
        fs.fclose(fd);
    }
    else
    {
        trace_msg(@"failed to open file");
    }
}

void MainController::act_bundle()
{
    ns::URL target = ns::URL::Bundle(@"data.bundle");
    ns::URL des = ns::Directory::Variable(@"data.bundle");
    if (ns::Directory::isDir(des))
        trace_msg(@"is exist.");
    else
        ns::Local::copy(des, target);
}

NNTAPP_END
