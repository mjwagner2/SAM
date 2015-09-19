#ifndef __MonthByHourFactorCtrl_h
#define __MonthByHourFactorCtrl_h

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/grid.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include <wx/aui/auibook.h>
#include <wx/imaglist.h>
#include <wx/spinctrl.h>
#include <wx/spinbutt.h>

#include <wex/numeric.h>

#include "object.h"

class VarValue;
class AFMonthByHourFactorCtrl;

/* utility class to save/load shading data */
struct ShadingInputData
{
	ShadingInputData();

	bool en_hourly;
	std::vector<float> hourly;

	bool en_timestep;
	matrix_t<float> timestep;

	bool en_mxh;
	matrix_t<float> mxh;

	bool en_azal;
	matrix_t<float> azal;

	bool en_diff;
	double diff;

	void clear();
	void save( std::vector<float> &data );
	bool load( const std::vector<float> &data );

	void write( VarValue *vv );
	bool read( VarValue *vv );

	
};

#define EVT_SHADINGBUTTON(i,f) EVT_BUTTON(i,f)
class ShadingButtonCtrl : public wxButton
{
public:
	ShadingButtonCtrl( wxWindow *parent, int id, 
		const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize);

	void Write( VarValue * );
	bool Read( VarValue * );
	void SetDescription( const wxString &s ) { m_descText = s; }
	void OnPressed(wxCommandEvent &evt);

private:
	ShadingInputData m_shad;
	wxString m_descText;
	DECLARE_EVENT_TABLE();
};


/* custom control for shading fractions for each parallel string (up to 8) in each subarray (up to 4)  can move to widgets or wex if necessary */
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_wxSpinBoxGridCtrl_CHANGE, 0)
END_DECLARE_EVENT_TYPES()



class wxSpinBoxGridCtrl : public wxPanel
{
public:
	wxSpinBoxGridCtrl(wxWindow *parent, int id,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &sz = wxDefaultSize,
		bool sidebuttons = false);

	void SetData(const matrix_t<float> &mat);
	void GetData(matrix_t<float> &mat);
	matrix_t<float> GetData() const { return m_data; }


	void SetCaption(const wxString &cap);
	wxString GetCaption();


	void ShowCols(bool b);
	bool ShowCols();

	void ShowColLabels(bool b);
	bool ShowColLabels();

	void SetColLabels(const wxArrayString &colLabels);
	wxArrayString GetColLabels();

	int GetNumCols() { return m_num_cols; }
	int GetNumRows() { return m_num_rows; }

	void SetNumCols(int &cols);
	void SetNumRows(int &rows);

private:

//	wxString m_rowFormat;
//	wxString m_colFormat;

	matrix_t<float> m_data;
	wxExtGridCtrl *m_grid;
	wxStaticText *m_caption;
	wxSpinCtrl *m_spin;

	int m_num_cols;
	int m_num_rows;

	void OnCellChange(wxGridEvent &evt);
	void OnCommand(wxCommandEvent &evt);
	void OnSpin(wxSpinEvent  &evt);


	void MatrixToGrid();

	DECLARE_EVENT_TABLE();
};





bool ImportPVsystNearShading( ShadingInputData &dat, wxWindow *parent = 0 );
bool ImportSunEyeHourly( ShadingInputData &dat, wxWindow *parent = 0 );
bool ImportSunEyeObstructions( ShadingInputData &dat, wxWindow *parent = 0 );
bool ImportSolPathMonthByHour( ShadingInputData &dat, wxWindow *parent = 0 );







#endif

