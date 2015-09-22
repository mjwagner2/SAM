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
	/* version 2 */
//	bool en_hourly;
//	std::vector<float> hourly;

	/* version 3 */
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


	void SetColCaption(const wxString &cap);
	wxString GetColCaption();

	void SetMinuteCaption(const wxString &cap);
	wxString GetMinuteCaption();


	void ShowCols(bool b);
	bool ShowCols();

	void ShowColLabels(bool b);
	bool ShowColLabels();

	void SetColLabels(const wxArrayString &colLabels);
	wxArrayString GetColLabels();

	void SetColLabelFormatString(const wxString &col_format_str);
	wxString GetColLabelFormatString() { return m_col_format_str; }

	size_t GetNumCols() { return m_num_cols; }
	void SetNumCols(size_t &cols);

	size_t GetNumRows() { return m_num_rows; }
	void SetNumRows(size_t &rows);

	size_t GetNumMinutes() { return m_num_minutes; }
	void SetNumMinutes(size_t &minutes);

	void SetDefaultValue(float &default_val) { m_default_val=default_val; }
	float GetDefaultValue() { return m_default_val; }

	void SetMinimumNumberCols(int &min_cols);
	size_t GetMinimumNumberCols() { return m_min_cols; }

	void SetMaximumNumberCols(int &max_cols);
	int GetMaximumNumberCols() { return m_max_cols; }

	void SetMinimumNumberMinutes(int &min_minutes);
	int GetMinimumNumberMinutes() { return m_min_minutes; }

	void SetMaximumNumberMinutes(int &max_minutes);
	int GetMaximumNumberMinutes() { return m_max_minutes; }

private:
	void UpdateNumberColumns(size_t &new_cols);
	void UpdateNumberRows(size_t &new_rows);
	void UpdateNumberMinutes(size_t &new_minutes);
	void UpdateColumnHeaders();

	bool m_col_header_use_format;
	wxArrayString m_col_ary_str;
	wxString m_col_format_str;
	float m_default_val;
	int m_min_cols;
	int m_max_cols;
	int m_min_minutes;
	int m_max_minutes;
	matrix_t<float> m_data;
	wxExtGridCtrl *m_grid;
	wxStaticText *m_caption_col;
	wxSpinCtrl *m_spin_col;
	wxStaticText *m_caption_minute;
	wxSpinCtrl *m_spin_minute;

	size_t m_num_cols;
	size_t m_num_rows;
	size_t m_num_minutes;

	void OnCellChange(wxGridEvent &evt);
	void OnCommand(wxCommandEvent &evt);
	void OnSpinCol(wxSpinEvent  &evt);
	void OnSpinMinute(wxSpinEvent  &evt);


	void MatrixToGrid();

	DECLARE_EVENT_TABLE();
};





bool ImportPVsystNearShading( ShadingInputData &dat, wxWindow *parent = 0 );
bool ImportSunEyeHourly( ShadingInputData &dat, wxWindow *parent = 0 );
bool ImportSunEyeObstructions( ShadingInputData &dat, wxWindow *parent = 0 );
bool ImportSolPathMonthByHour( ShadingInputData &dat, wxWindow *parent = 0 );







#endif

