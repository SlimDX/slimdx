<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0"
               xmlns:date="http://exslt.org/dates-and-times">
  
  <xsl:output method="text"/>
  <xsl:strip-space elements="*"/>

  <xsl:template match="/">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="documented-type">
    <xsl:value-of select="concat('&lt;page&gt;&#xa;&lt;title&gt;',@longname,'&lt;/title&gt;&#xa;')"/>
    <xsl:value-of select="concat('&lt;revision&gt;&#xa;&lt;timestamp&gt;',date:date-time(),'&lt;/timestamp&gt;&#xa;')"/>
    <xsl:value-of select="'&lt;text&gt;&#xa;'"/>

    <xsl:apply-templates select="./discussion"/>
    <xsl:if test="./documented-method">
      <xsl:value-of select="'== Methods ==&#xa;'"/>
      <xsl:apply-templates select="./documented-method"/>
    </xsl:if>
    <xsl:if test="./documented-property">
      <xsl:value-of select="'== Properties ==&#xa;'"/>
      <xsl:apply-templates select="./documented-property"/>
    </xsl:if>

    <xsl:value-of select="'&lt;/text&gt;&#xa;'"/>
    <xsl:value-of select="'&lt;/revision&gt;&#xa;'"/>
    <xsl:value-of select="'&lt;/page&gt;&#xa;'"/>
  </xsl:template>

  <xsl:template match="documented-method">
    <xsl:value-of select="concat('===== ',@name,' =====&#xa;')"/>
    <xsl:if test="./parameter">
      <xsl:value-of select="'{|&#xa;'"/>
      <xsl:for-each select="./parameter">
        <xsl:choose>
          <xsl:when test="starts-with(@longtype,'SlimDX')">
            <xsl:value-of select="concat('|-&#xa;| [[',@longtype,'|',@shorttype,']] || ',@name,' || ')"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of select="concat('|-&#xa;| ',@shorttype,' || ',@name,' || ')"/>
          </xsl:otherwise>
        </xsl:choose>
        <xsl:apply-templates select="."/>
        <xsl:value-of select="'&#xa;'"/>
      </xsl:for-each>
      <xsl:value-of select="'|}&#xa;'"/>
      <xsl:apply-templates select="./discussion"/>
      <xsl:apply-templates select="./return-value"/>
    </xsl:if>
  </xsl:template>

  <xsl:template match="documented-property">
    <xsl:value-of select="concat('===== ',@name,' =====&#xa;')"/>
    <xsl:apply-templates select="./discussion"/>
  </xsl:template>

  <xsl:template match="parameter">
    <xsl:apply-templates/>
  </xsl:template>
  
  <xsl:template match="return-value">
    <xsl:apply-templates/>
  </xsl:template>
  
  <xsl:template match="discussion">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="pagelink">
    <xsl:value-of select="concat('[[',@target,']]')"/>
  </xsl:template>
  
</xsl:transform>
