/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- IRenderEngine.hpp

Abstract:
- This serves as the entry point for a specific graphics engine specific renderer.

Author(s):
- Michael Niksa (MiNiksa) 17-Nov-2015
--*/

#pragma once

#include "CursorOptions.h"
#include "Cluster.hpp"
#include "FontInfoDesired.hpp"
#include "IRenderData.hpp"
#include "../../buffer/out/LineRendition.hpp"

namespace Microsoft::Console::Render
{
    struct RenderFrameInfo
    {
        std::optional<CursorOptions> cursorInfo;
    };

    class IRenderEngine
    {
    public:
        enum GridLines
        {
            None = 0x0,
            Top = 0x1,
            Bottom = 0x2,
            Left = 0x4,
            Right = 0x8,
            Underline = 0x10,
            DoubleUnderline = 0x20,
            Strikethrough = 0x40,
            HyperlinkUnderline = 0x80
        };

        constexpr IRenderEngine() = default;
        virtual ~IRenderEngine(){};

        IRenderEngine(const IRenderEngine&) = delete;
        IRenderEngine& operator=(const IRenderEngine&) = delete;

        IRenderEngine(IRenderEngine&&) = default;
        IRenderEngine& operator=(IRenderEngine&&) = default;

        [[nodiscard]] virtual HRESULT StartPaint() noexcept = 0;
        [[nodiscard]] virtual HRESULT EndPaint() noexcept = 0;
        [[nodiscard]] virtual bool RequiresContinuousRedraw() noexcept = 0;
        virtual void WaitUntilCanRender() noexcept = 0;
        [[nodiscard]] virtual HRESULT Present() noexcept = 0;
        [[nodiscard]] virtual HRESULT PrepareForTeardown(_Out_ bool* const pForcePaint) noexcept = 0;
        [[nodiscard]] virtual HRESULT ScrollFrame() noexcept = 0;
        [[nodiscard]] virtual HRESULT Invalidate(const SMALL_RECT* const psrRegion) noexcept = 0;
        [[nodiscard]] virtual HRESULT InvalidateCursor(const SMALL_RECT* const psrRegion) noexcept = 0;
        [[nodiscard]] virtual HRESULT InvalidateSystem(const RECT* const prcDirtyClient) noexcept = 0;
        [[nodiscard]] virtual HRESULT InvalidateSelection(const std::vector<SMALL_RECT>& rectangles) noexcept = 0;
        [[nodiscard]] virtual HRESULT InvalidateScroll(const COORD* const pcoordDelta) noexcept = 0;
        [[nodiscard]] virtual HRESULT InvalidateAll() noexcept = 0;
        [[nodiscard]] virtual HRESULT InvalidateCircling(_Out_ bool* const pForcePaint) noexcept = 0;
        [[nodiscard]] virtual HRESULT InvalidateTitle() noexcept = 0;
        [[nodiscard]] virtual HRESULT PrepareRenderInfo(const RenderFrameInfo& info) noexcept = 0;
        [[nodiscard]] virtual HRESULT ResetLineTransform() noexcept = 0;
        [[nodiscard]] virtual HRESULT PrepareLineTransform(const LineRendition lineRendition, const size_t targetRow, const size_t viewportLeft) noexcept = 0;
        [[nodiscard]] virtual HRESULT PaintBackground() noexcept = 0;
        [[nodiscard]] virtual HRESULT PaintBufferLine(gsl::span<const Cluster> const clusters, const COORD coord, const bool fTrimLeft, const bool lineWrapped) noexcept = 0;
        [[nodiscard]] virtual HRESULT PaintBufferGridLines(const GridLines lines, const COLORREF color, const size_t cchLine, const COORD coordTarget) noexcept = 0;
        [[nodiscard]] virtual HRESULT PaintSelection(const SMALL_RECT rect) noexcept = 0;
        [[nodiscard]] virtual HRESULT PaintCursor(const CursorOptions& options) noexcept = 0;
        [[nodiscard]] virtual HRESULT UpdateDrawingBrushes(const TextAttribute& textAttributes, const gsl::not_null<IRenderData*> pData, const bool usingSoftFont, const bool isSettingDefaultBrushes) noexcept = 0;
        [[nodiscard]] virtual HRESULT UpdateFont(const FontInfoDesired& FontInfoDesired, _Out_ FontInfo& FontInfo) noexcept = 0;
        [[nodiscard]] virtual HRESULT UpdateSoftFont(const gsl::span<const uint16_t> bitPattern, const SIZE cellSize, const size_t centeringHint) noexcept = 0;
        [[nodiscard]] virtual HRESULT UpdateDpi(const int iDpi) noexcept = 0;
        [[nodiscard]] virtual HRESULT UpdateViewport(const SMALL_RECT srNewViewport) noexcept = 0;
        [[nodiscard]] virtual HRESULT GetProposedFont(const FontInfoDesired& FontInfoDesired, _Out_ FontInfo& FontInfo, const int iDpi) noexcept = 0;
        [[nodiscard]] virtual HRESULT GetDirtyArea(gsl::span<const til::rectangle>& area) noexcept = 0;
        [[nodiscard]] virtual HRESULT GetFontSize(_Out_ COORD* const pFontSize) noexcept = 0;
        [[nodiscard]] virtual HRESULT IsGlyphWideByFont(const std::wstring_view glyph, _Out_ bool* const pResult) noexcept = 0;
        [[nodiscard]] virtual HRESULT UpdateTitle(const std::wstring_view newTitle) noexcept = 0;
    };
}

#pragma warning(suppress : 26812) // The enum type '...' is unscoped. Prefer 'enum class' over 'enum' (Enum.3).
DEFINE_ENUM_FLAG_OPERATORS(Microsoft::Console::Render::IRenderEngine::GridLines)
